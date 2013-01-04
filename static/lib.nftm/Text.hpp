#ifndef   NFTM_static_src_bin_static_lib_nftm_Text_HPP
#define   NFTM_static_src_bin_static_lib_nftm_Text_HPP

namespace NFTM {
    
    class Text {
    public:
        Text(void);
        Text(const char *str);
        Text(const char *str, int length);
        Text(const char *str1, const char *str2);
        Text(Text *text);
        Text(Text *text, int length);
        Text(Text *text1, Text *text2);
        Text(Text *fileName, bool forceNewLine, bool trimTrailingNewline);
        ~Text();
        
        bool Equals(const char *str) const;
        bool IsNull(void) const {
            return isNull;
        }
        bool IsTainted(void) const {
            return isTainted;
        }

        Text *PullText(void) const;
        Text *PullVariables(void) const;

        bool  isNull;
        bool  isTainted;
        char *text;
    }; // class Text
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_lib_nftm_Text_HPP
