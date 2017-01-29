#ifndef _MKDIO_CXX
#define _MKDIO_CXX

extern "C" {
#include <stdio.h>
#include <mkdio.h>
}

class MKIOT {
protected:
    void *mmiot;
    MKIOT()				{ mmiot=0;} /* dummy initializer */

public:
    MKIOT(FILE* in, mkd_flag_t flags)	{ mmiot = mkd_in(in,flags); }
    MKIOT(const char *text, int size, mkd_flag_t flags)
					{ mmiot = mkd_string(text, size, flags); }
    ~MKIOT()				{ mkd_cleanup(mmiot); }

    void basename(char* name)		{ mkd_basename(mmiot,name); }
    int  compile(mkd_flag_t flags)	{ return mkd_compile(mmiot,flags); }
    int  dump(FILE *out, int flags, char *text)
					{ return mkd_dump(mmiot,out,flags,text); }
    int  format(FILE *out, int flags)	{ return this->compile(flags)
					      && this->generatehtml(out); }
    int  xhtmlpage(mkd_flag_t flags, FILE *out)
					{ return mkd_xhtmlpage(mmiot,flags,out); }
    char *doc_title()			{ return mkd_doc_title(mmiot); }
    char *doc_author()			{ return mkd_doc_author(mmiot); }
    char *doc_date()			{ return mkd_doc_date(mmiot); }
    int document(char **buf_p)		{ return mkd_document(mmiot, buf_p); }
    int toc(char **buf_p)		{ return mkd_toc(mmiot, buf_p); }
    int css(char **buf_p)		{ return mkd_css(mmiot, buf_p); }

    int generatehtml(FILE *out)		{ return mkd_generatehtml(mmiot, out); }
    int generatetoc(FILE *out)		{ return mkd_generatetoc(mmiot, out); }
    int generatecss(FILE *out)		{ return mkd_generatecss(mmiot, out); }
    int style(FILE *out)		{ return this->generatecss(out); }

    void e_url(mkd_callback_t f)	{ mkd_e_url(mmiot, f); }
    void e_flags(mkd_callback_t f)	{ mkd_e_flags(mmiot, f); }
    void e_free(mkd_free_t f)		{ mkd_e_free(mmiot, f); }
    void e_data(void *ptr)		{ mkd_e_data(mmiot, ptr); }

    char *version()			{ return markdown_version; }
    void mmiot_flags(FILE *out, int html)
					{ mkd_mmiot_flags(out,mmiot,html); }
    void ref_prefix(char *pfx)		{ mkd_ref_prefix(mmiot, pfx); }
} ;

class GFIOT: MKIOT {
    GFIOT(FILE *in, mkd_flag_t flags)	{ mmiot = gfm_in(in,flags); }
    GFIOT(const char *text, int size, mkd_flag_t flags)
					{ mmiot = gfm_string(text, size, flags); }
} ;

#endif/*_MKDIO_CXX*/