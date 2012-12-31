#ifndef   NFTM_static_src_bin_static_lib_nftm_Template_HPP
#define   NFTM_static_src_bin_static_lib_nftm_Template_HPP

namespace NFTM {
    
    //---------------------------------------------------------------------------
    // Template
    //    retrieves a template from some source and saves it in memory as
    //    a nil-terminated string.
    //
    //
    class Template {
    public:
        Template(void) { data = 0; }
        virtual ~Template() { delete [] data; };

        virtual class AST *Load(void) = 0;

        char *data;
    }; // class Template

    class TemplateFile : public Template {
    public:
        TemplateFile(const char *source);
        ~TemplateFile();

        class AST *Load(void);

        char *source;
    }; // class TemplateFile

    class TemplateText : public Template {
    public:
        TemplateText(const char *text);
        ~TemplateText();
        
        class AST *Load(void);

        char *text;
    }; // class TemplateText

} // namespace NFTM

#endif // NFTM_static_src_bin_static_lib_nftm_Template_HPP
