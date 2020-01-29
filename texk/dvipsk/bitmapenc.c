/*
 *   This file implements support for adding proper character encodings to
 *   bitmap fonts, so searching and copying text works better in PDFs
 *   generated by the dvips Postscript output that uses bitmap fonts.
 *
 *   Written by Tomas Rokicki in June/July 2019. Public domain.
 *   The dvips-all.enc file used here is also public domain.
 *
 *   It turns out we need to do more than just add encodings to the fonts
 *   for most PDF viewers, so this file also takes care of those issues.
 */
/*
 *   Our first concern is finding and reading encoding files for bitmap
 *   fonts, and, if such cannot be found, determining a reasonable
 *   alternative.
 *
 *   We could use the code in writet1 to read an encoding file, but
 *   we would need to make some messy changes for that to work, and we
 *   really want this to be a minimal impact to existing code (especially
 *   code such as write_t1 that we don't have a good handle on).
 *
 *   We want to deduplicate (combine identical) encodings to lower the
 *   memory and file size impact.  But we have to be careful; if the
 *   document requires multiple sections, we need to redownload encodings
 *   just like we do fonts.
 */
#include <stdio.h>
#include <string.h>
#ifndef STANDALONE
#include <kpathsea/config.h>
#endif
#include "dvips.h"
#include "protos.h"
/*
 *   Do we use this functionality?  If 0, then no; if 1, then yes, but
 *   suppress warnings; if 2, then warn.
 */
int encodetype3 = 1 ;
void bitmapencopt(int v) {
   if (0 <= v && v <= 2)
      encodetype3 = v ;
   else
      error("! Bad option to J") ;
}
/*
 *   TODO
 *
 *   Initially we support standalone compilation for testing but
 *   this code will be ripped out before release.
 */
#ifdef STANDALONE
#undef fopen
#undef fclose
#endif
/*
 *   Reading the encodings.
 *
 *   Encodings we read are returned as an array C strings.  We do not
 *   attempt to parse the contents of the encodings, because they
 *   may contain additional dictionaries or other PostScript code
 *   that can possibly do more advanced things.
 */
#define MAX_LINE_LENGTH 256
/*
 *   A structure for storing deduplicated encodings.  These are deduplicated
 *   in dvips memory on load.  We also store information on whether the
 *   encoding has been downloaded in a particular section.  This is stored
 *   as a singly-linked list for all distinct encodings we have used so
 *   far.
 */
struct bmenc {
   const char **enc ;   // the encoding itself
   int downloaded_seq ; // -1: not downloaded; else, sequence number
   struct bmenc *next ; // next encoding in linear linked list
   unsigned char existsbm[32] ; // a bitmap of characters with names
} ;
static struct bmenc *bmlist ;
/*
 *   This structure maintains a relationship between a font name and a
 *   bitmap encoding.  Again, linear search is used.
 */
struct bmfontenc {
   const char *fontname ;   // dvi font name
   struct bmenc *enc ;      // the encoding to use
   struct bmfontenc *next ; // next encoding
} ;
static struct bmfontenc *bmfontenclist ;
/*
 *   We load the default encodings for all fonts en masse from he
 *   dvips-all.enc file, and store them here.  We use an array and
 *   sort the input for quicker search.  We don't need to deduplicate
 *   because we assume whatever generated dvips-all.enc already did
 *   deduplication.
 */
static int numstatic ;
static struct allfontenc {
   const char *fontname ;
   const char **enc ;
} *bmfontarr ;
/*
 *   While loading dvips-all.enc, we track the capacity of our allfontenc
 *   array, how many have names, the capacity in strings of our encoding
 *   that is being built up, and how many strings we still can store in
 *   the encoding built up.
 */
static int capstatic, namedstatic ;
static int in_working_enc, working_enc_left ;
const char **working_enc ;
/*
 *   Add another fontname to the list (from the dvips-all.enc file).
 *   If needed expand the working arrays.  If there is currently
 *   an encoding, that means that we need to first assign that
 *   encoding to the list of font names we have built up, so do
 *   that first.  If the fontname passed is the null string, this is
 *   the last call done just to finish up the last encoding.
 */
static void add_fontname(const char *fontname) {
   int i ;
   if (in_working_enc) { // flush
      const char **e = working_enc ;
      while (numstatic < namedstatic)
         bmfontarr[numstatic++].enc = e ;
      working_enc += in_working_enc + 1 ;
      working_enc_left -= in_working_enc + 1 ;
      in_working_enc = 0 ;
   }
   if (fontname == 0)
      return ;
   if (namedstatic >= capstatic) {
      int ncapstatic = capstatic * 2 + 20 ;
      struct allfontenc *nbmfontarr =
        (struct allfontenc *)mymalloc(sizeof(struct allfontenc) * ncapstatic) ;
      if (capstatic) {
         memcpy(nbmfontarr, bmfontarr, sizeof(struct allfontenc)*capstatic) ;
         free(bmfontarr) ;
      }
      bmfontarr = nbmfontarr ;
      for (i=capstatic; i<ncapstatic; i++) {
         bmfontarr[i].fontname = 0 ;
         bmfontarr[i].enc = 0 ;
      }
      capstatic = ncapstatic ;
   }
   bmfontarr[namedstatic].fontname = fontname ;
   bmfontarr[namedstatic].enc = 0 ;
   namedstatic++ ;
}
/*
 *   Add an encoding line to the working encoding; if needed, reallocate
 *   the working array.
 */
static void add_encline(const char *encline) {
   if (in_working_enc + 1 >= working_enc_left) {
      int i ;
      int new_enc_size = 100 + 2 * in_working_enc ;
      const char **new_working_enc =
               (const char **)mymalloc(sizeof(const char **) * new_enc_size) ;
      for (i=0; i<new_enc_size; i++)
         new_working_enc[i] = 0 ;
      for (i=0; i<in_working_enc; i++)
         new_working_enc[i] = working_enc[i] ;
      working_enc = new_working_enc ;
      working_enc_left = new_enc_size - in_working_enc ;
   }
   working_enc[in_working_enc++] = encline ;
}
/*
 *   Parse the encoding file.  If use_all flag is set then we are parsing
 *   the dvips_all file which can have multiple encodings, each preceded
 *   by a set of lines with font names followed by a colon character.
 *
 *   If we are parsing them all, we build a sorted global list of entries
 *   for later lookup, and always return 0.  Otherwise we just expect a
 *   single encoding and we store that away.
 */
static const char **parseencodingfile(FILE *f, int use_all) {
   char encbuf[MAX_LINE_LENGTH+1] ;
   size_t i ;
   for (i=0; i<sizeof(encbuf); i++)
      encbuf[i] = 0 ;
   while (fgets(encbuf, MAX_LINE_LENGTH, f) != 0) {
      char *p = encbuf ;
      char *q = p + strlen(p) - 1 ;
      while (q > p && *q < ' ') // kill line terminators
         *q-- = 0 ;
      q = p ;
      while (*q && *q != ' ' && *q != ':')
         q++ ;
      if (use_all && *q == ':') { // looks like a font name
         if (q[1] >= ' ' || !use_all)
            error(
       "! unexpected colon or extra stuff at end of line in encoding file?") ;
         *q = 0 ;
         add_fontname(strdup(p)) ;
      } else {
         add_encline(strdup(p)) ;
      }
   }
   if (use_all)
      add_fontname(0) ; // flushes last encoding
   if (use_all) {
      // sort the static fonts for quicker search; Shell sort
      int h = 1 ;
      while (h < numstatic)
         h = 3 * h + 1 ;
      while (h > 1) {
         int i ;
         h /= 3 ;
         for (i=h; i<numstatic; i++) {
            int j = i ;
            while (j >= h &&
                   strcmp(bmfontarr[j-h].fontname, bmfontarr[j].fontname) > 0) {
               const char *na = bmfontarr[j-h].fontname ;
               const char **en = bmfontarr[j-h].enc ;
               bmfontarr[j-h].fontname = bmfontarr[j].fontname ;
               bmfontarr[j-h].enc = bmfontarr[j].enc ;
               bmfontarr[j].fontname = na ;
               bmfontarr[j].enc = en ;
               j -= h ;
            }
         }
      }
      return 0 ;
   } else {
      const char **e = working_enc ;
      if (e == 0)
         error("! No lines in encoding?") ;
      return e ;
   }
}
/*
 *   Given a font name, find an encoding file.  We prefix all encoding
 *   files with "dvips-" to distinguish these encodings from those used
 *   in the psfonts.map, since the syntax, requirements, and function
 *   is somewhat different.
 */
#define MAX_NAME_SIZE 256
static FILE *bitmap_enc_search(const char *fontname) {
   char namebuf[MAX_NAME_SIZE+1] ;
   if (fontname == 0 || strlen(fontname) > 128)
      error("! excessively long font name") ;
   sprintf(namebuf, "dvips-%s.enc", fontname) ;
#ifdef STANDALONE
   return fopen(namebuf, FOPEN_RBIN_MODE) ;
#else
   return search(kpse_enc_format, namebuf, FOPEN_RBIN_MODE) ;
#endif
}
/*
 *   Are two raw encodings identical?  They must be exactly the same; there
 *   is no effort towards comparing semantics, just precise text.
 */
static int eqencoding(const char **a, const char **b) {
   int i ;
   if (a == b)
      return 1 ;
   for (i=0; a[i] != 0 && b[i] != 0; i++)
      if (a[i] != b[i] && (a[i] == 0 || b[i] == 0 || strcmp(a[i], b[i]) != 0))
         return 0 ;
   return 1 ;
}
/*
 *   Try to parse an encoding to identify which names exist and which don't.
 *   If we can't trivially parse it we just mark all names as existing.
 *   We properly parse the following types of tokens:
 *   [ (at start) ] (at end) : ignored
 *   /name
 *   digits { /.notdef } repeat
 *
 *   In all cases the spaces and linebreaks are arbitrary.
 *
 *   The state machine works as follows:
 *
 *   'B':  begin; expect [
 *   'N':  between entries; expect name or digits or ]
 *   'E':  finished (saw ]); expect nothing more
 *   '#':  just saw digits; expect only {
 *   '{':  just saw {; expect only name and should be /.notdef
 *   'L':  just saw a name inside {}; expect only }
 *   '}':  just saw }; expect only repeat
 */
static int trytoparseenc(struct bmenc *bme) {
   int i ;
   const char **enc = bme->enc ;
   const char *p ;
   int seenchars = 0 ;
   int num = 0 ;
   char state = 'B' ;
   for (i=0; i<32; i++)
      bme->existsbm[i] = 255 ;
   while (*enc != 0) {
      p = *enc ;
      enc++ ;
      while (*p && *p <= ' ')
         p++ ;
      while (*p != 0) {
         switch (state) {
case 'B':   if (*p != '[') return 0 ;
            p++ ;
            state = 'N' ;
            break ;
case 'N':   if (*p == ']') {
               p++ ;
               state = 'E' ;
            } else if (*p == '/') {
               if (seenchars >= 256)
                  return 0 ;
               if (strncmp(p, "/.notdef", 8) == 0 &&
                   (p[8] <= ' ' || index("{}[]<>()%/", p[8]) == 0)) {
                  bme->existsbm[seenchars>>3] &= ~(1<<(seenchars & 7)) ;
               }
               // see PostScript language reference manual syntax for this
               p++ ;
               while (*p > ' ' && index("{}[]<>()%/", *p) == 0)
                  p++ ;
               seenchars++ ;
            } else if ('0' <= *p && *p <= '9') {
               num = 0 ;
               while (num < 256 && '0' <= *p && *p <= '9')
                  num = 10 * num + *p++ - '0' ;
               state = '#' ;
            } else
               return 0 ;
            break ;
case '#':   if (*p != '{') return 0 ;
            p++ ;
            state = '{' ;
            break ;
case '{':   if (strncmp(p, "/.notdef", 8) != 0)
               return 0 ;
            p += 8 ;
            if (*p > ' ' && index("{}[]<>()%/", *p) == 0)
               return 0 ;
            while (num > 0) {
               if (seenchars >= 256)
                  return 0 ;
               bme->existsbm[seenchars>>3] &= ~(1<<(seenchars & 7)) ;
               seenchars++ ;
               num-- ;
            }
            state = 'L' ;
            break ;
case 'L':   if (*p != '}')
               return 0 ;
            p++ ;
            state = '}' ;
            break ;
case '}':   if (strncmp(p, "repeat", 6) != 0)
               return 0 ;
            p += 6 ;
            state = 'N' ;
            break ;
default:
            error("! internal error in encoding vector parse") ;
         }
         while (*p && *p <= ' ')
            p++ ;
      }
   }
   if (seenchars != 256)
      return 0 ;
   return 1 ;
}
static void parseenc(struct bmenc *bme) {
   int i ;
   if (trytoparseenc(bme) == 0) {
      printf("Failed to parse it.\n") ;
      for (i=0; i<32; i++)
         bme->existsbm[i] = 255 ;
   }
}
/*
 *   Add an encoding to our list of deduplicated encodings.
 */
struct bmenc *addbmenc(const char **enc) {
   struct bmenc *r = (struct bmenc *)mymalloc(sizeof(struct bmenc)) ;
   r->downloaded_seq = -1 ;
   r->enc = enc ;
   r->next = bmlist ;
   parseenc(r) ;
   bmlist = r ;
   return r ;
}
/*
 *   Given a particular encoding, walk through our encoding list and
 *   see if it already exists; if so, return the existing one.
 *   The set of distinct encodings in a particular document is
 *   expected to be small (a few dozen at most).
 */
static struct bmenc *deduplicateencoding(const char **enc) {
   struct bmenc *p ;
   for (p=bmlist; p!=0; p=p->next)
      if (eqencoding(p->enc, enc))
         return p ;
   return addbmenc(enc) ;
}
/*
 *   Attempt to load an encoding; first, find the file, and then parse
 *   the file.
 */
static const char **bitmap_enc_load(const char *fontname, int use_all) {
   FILE *f = bitmap_enc_search(use_all ? "all" : fontname) ;
   if (f != 0) {
      const char **r = parseencodingfile(f, use_all) ;
      fclose(f) ;
      return r ;
   }
   return 0 ;
}
/*
 *   Start a section: mark all encodings as not downloaded yet.
 */
static int curbmseq ;
void bmenc_startsection() {
   struct bmenc *p ;
   for (p=bmlist; p!=0; p=p->next)
      p->downloaded_seq = -1 ;
   curbmseq = 0 ;
}
/*
 *   Try to find a font in the all encoding list.  This list is sorted
 *   so we can use binary search.
 */
static const char **bitmap_all_find(const char *fontname) {
   int ptr, bit;
   if (numstatic == 0)
      return 0 ;
   ptr = 0 ;
   bit = 1 ;
   while ((bit << 1) < numstatic)
      bit <<= 1 ;
   while (bit > 0) {
      int t = ptr + bit ;
      if (t < numstatic && strcmp(fontname, bmfontarr[t].fontname) >= 0)
         ptr = t ;
      bit >>= 1 ;
   }
   if (strcmp(fontname, bmfontarr[ptr].fontname) == 0)
      return bmfontarr[ptr].enc ;
   else
      return 0 ;
}
/*
 *   Download the encoding and set the sequence number.
 */
static void downloadenc(struct bmenc *enc) {
   int fresh = 0 ;
   char cmdbuf[16] ;
   if (enc->downloaded_seq < 0) {
      int i ;
      newline() ;
      for (i=0; enc->enc[i]; i++)
         pslineout(enc->enc[i]) ;
      enc->downloaded_seq = curbmseq++ ;
      fresh = 1 ;
   }
   newline() ;
   sprintf(cmdbuf, "/EN%d", enc->downloaded_seq) ;
   if (fresh) {
      cmdout("A") ;
      psnameout(cmdbuf) ;
      cmdout("X") ;
   } else {
      // we use load here specifically to defer execution until the
      // new font dictionary is on the stack and being built.
      psnameout(cmdbuf) ;
      cmdout("load") ;
   }
}
/*
 *   Send out the new encoding, font bounding box, and font matrix.
 *   If we cannot find an encoding file for this font, do what we
 *   used to do instead (don't give it an encoding or resize or
 *   rescale).
 */
static struct bmenc *getencoding_seq(const char *fontname) ;
int downloadbmencoding(const char *name, double scale, fontdesctype *curfnt) {
   int slop;
   int i ;
   int seq ;
   int llx = curfnt->llx ;
   int lly = curfnt->lly ;
   int urx = curfnt->urx ;
   int ury = curfnt->ury ;
   struct bmenc *bme = getencoding_seq(name) ;
   if (bme == 0)
      return -1 ;
   seq = bme->downloaded_seq ;
/*
 *   Check that every character defined in the font has a name in the
 *   PostScript vector, and complain if this is not the case.
 */
   for (i=0; i<256 && i<curfnt->maxchars; i++) {
      if ((curfnt->chardesc[i].flags2 & EXISTS) &&
                                !(bme->existsbm[i>>3] & (1 << (i & 7)))) {
         fprintf(stderr,
"Can't use PostScript encoding vector for font %s; character %d has no name.\n",
         name, i) ;
         return -1 ;
      }
   }
   cmdout("IEn") ;
   cmdout("S") ;
   psnameout("/IEn") ;
   cmdout("X") ;
   cmdout("FBB") ;
   cmdout("FMat") ;
   psnameout("/FMat") ;
   specialout('[') ;
   doubleout(1.0/scale) ;
   numout(0) ;
   numout(0) ;
   doubleout(-1.0/scale) ;
   numout(0) ;
   numout(0) ;
   specialout(']') ;
   cmdout("N") ;
   psnameout("/FBB") ;
   // we add a bit of slop here, because this is only used for
   // highlighting, and in theory if the bounding box is too
   // tight, on some RIPs, characters could be clipped.
   slop = 1;
   specialout('[') ;
   numout(llx-slop) ;
   numout(lly-slop) ;
   numout(urx+slop) ;
   numout(ury+slop) ;
   specialout(']') ;
   cmdout("N") ;
   newline() ;
   return seq ;
}
/*
 *   Finish up the downloaded encoding; scale the font, and restore the
 *   previous global definitions.
 */
void finishbitmapencoding(const char *name, double scale) {
   psnameout(name) ;
   cmdout("load") ;
   numout(0) ;
   cmdout(name+1) ;
   cmdout("currentfont") ;
   doubleout(scale) ;
   cmdout("scalefont") ;
   cmdout("put") ;
   psnameout("/FMat") ;
   cmdout("X") ;
   psnameout("/FBB") ;
   cmdout("X") ;
   psnameout("/IEn") ;
   cmdout("X") ;
   newline();
}
/*
 *   We warn if we have to use a built-in encoding, and set this value to 1.
 *   We warn again if we cannot find a built-in encoding and have to
 *   default to previous behavior, and set this value to 2.  In any case,
 *   we only issue warnings if the encodetype3 flag is set to a value greater
 *   than one; we don't want to bother folks about this new functionality.
 */
static int warned_about_missing_encoding = 0 ;
/*
 *   Print a warning message.
 */
static void bmenc_warn(const char *fontname, const char *msg) {
   if (encodetype3 > 1)
      fprintf(stderr,
         "dvips: Static bitmap font encoding for font %s (and others?): %s.\n",
                   fontname, msg) ;
}
/*
 *   About to download a font; find the encoding sequence number.
 *   If needed, download a new sequence.  If we can't find one, use
 *   -1; this font may not work as well for copy/paste and text search.
 */
static int tried_all = 0 ; // have we tried to load dvips-all.enc
static struct bmenc *getencoding_seq(const char *fontname) {
   struct bmenc *enc = 0 ;
   struct bmfontenc *p = bmfontenclist ;
   for (; p!=0; p=p->next)
      if (strcmp(fontname, p->fontname) == 0) {
         enc = p->enc ;
         if (enc == 0) // remember failures
            return 0 ;
         break ;
      }
   // not in list; try to load it from a file
   if (enc == 0) {
      const char **e = bitmap_enc_load(fontname, 0) ;
      // did not find it; try to load it from the dvips-all list.
      if (e == 0) {
         if (!tried_all) {
            bitmap_enc_load(fontname, 1) ;
            tried_all = 1 ;
         }
         e = bitmap_all_find(fontname) ;
      }
      if (e)
         enc = deduplicateencoding(e) ;
   }
   // did not find this in the list; add it to the list
   if (p == 0) {
      p = (struct bmfontenc *)mymalloc(sizeof(struct bmfontenc)) ;
      p->fontname = strdup(fontname) ;
      p->enc = enc ;
      p->next = bmfontenclist ;
//    parseenc(enc) ;
      bmfontenclist = p ;
   }
   if (enc == 0) {
      if (warned_about_missing_encoding < 2) {
         bmenc_warn(fontname, "no encoding found") ;
         warned_about_missing_encoding = 2 ;
      }
      return 0 ; // don't download an encoding
   }
   downloadenc(enc) ;
   return enc ;
}
#ifdef STANDALONE
/*
 *   Standalone test code:
 */
void error(const char *s) {
   fprintf(stderr, "Failed: %s\n", s) ;
   if (*s == '!')
      exit(0) ;
}
char *mymalloc(int sz) {
   return (char *)malloc(sz) ;
}
int pos = 0 ;
int idok = 1 ;
const int MAXLINE = 75 ;
void newline() {
   printf("\n") ;
   idok = 1 ;
   pos = 0 ;
}
void doubleout(double f) {
   printf("%g", f) ;
   pos += 8 ;
}
void pslineout(const char *s) {
   printf("%s\n", s) ;
}
void numout(int num) {
   int len = 1 ;
   int t = num / 10 ;
   while (t>0) {
      len++ ;
      t /= 10 ;
   }
   if (pos + len >= MAXLINE)
      newline() ;
   if (!idok)
      specialout(' ') ;
   printf("%d", num) ;
   pos += len ;
   idok = 0 ;
}
void cmdout(const char *s) {
   if (pos + strlen(s) >= MAXLINE)
      newline() ;
   if (*s != '/' && !idok)
      specialout(' ') ;
   printf("%s", s) ;
   pos += strlen(s) ;
   idok = 0 ;
}
void psnameout(const char *s) {
   cmdout(s) ;
}
void specialout(char c) {
   if (pos + 1 >= MAXLINE)
      newline() ;
   printf("%c", c) ;
   pos++ ;
   idok = 1 ;
}
int main(int argc, char *argv[]) {
   bmenc_startsection() ;
   for (int i=1; i<argc; i++) {
      struct bmenc *r = getencoding_seq(argv[i]) ;
      int seq = r ? r->downloaded_seq : -1 ;
      printf("\n") ;
      printf("Result for %s is %d\n", argv[i], seq) ;
   }
}
#endif
