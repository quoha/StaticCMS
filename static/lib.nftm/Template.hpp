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
        Template(void);
        virtual ~Template();

        virtual class AST *Load(void) = 0;

        class Text *data;
    }; // class Template

    class TemplateFile : public Template {
    public:
        TemplateFile(class Text *fileName);
        ~TemplateFile();

        class AST *Load(void);

        class Text *fileName;
    }; // class TemplateFile

    class TemplateText : public Template {
    public:
        TemplateText(class Text *text);
        ~TemplateText();
        
        class AST *Load(void);

        class Text *text;
    }; // class TemplateText

} // namespace NFTM

#endif // NFTM_static_src_bin_static_lib_nftm_Template_HPP
