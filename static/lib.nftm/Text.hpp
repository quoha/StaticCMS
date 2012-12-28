#ifndef   NFTM_static_src_bin_static_Text_HPP
#define   NFTM_static_src_bin_static_Text_HPP

namespace NFTM {
    
    class Text {
    public:
        Text(void);
        Text(const char *str);
        Text(const char *str, int length);
        Text(Text *text);
        Text(Text *text, int length);
        ~Text();
        
        const char *AsCString(void) const;
        
        bool FromCString(const char *str);
        bool FromFile(const char *fileName, bool forceNewLine);
        bool IsNull(void) const {
            return isNull;
        }
        
        bool Copy(Text *q);
        void Release(void);
        
        bool  isNull;
        int   currLength;
        int   maxLength;
        char *data;
    }; // class Text
    
} // namespace NFTM

#endif // NFTM_static_src_bin_static_Text_HPP
