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

        bool  Execute(class SymbolTable *symtab, class Stack *stack);

        virtual bool Load(void) = 0;

        char *data;
    }; // class Template

    class TemplateFile : public Template {
    public:
        TemplateFile(const char *source);
        ~TemplateFile();

        bool Load(void);

        char *source;
    }; // class TemplateFile

    class TemplateText : public Template {
    public:
        TemplateText(const char *text);
        ~TemplateText();
        
        bool Load(void);

        char *text;
    }; // class TemplateText

} // namespace NFTM

#endif // NFTM_static_src_bin_static_lib_nftm_Template_HPP
