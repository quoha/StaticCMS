#ifndef   NFTM_static_src_bin_static_lib_nftm_Util_HPP
#define   NFTM_static_src_bin_static_lib_nftm_Util_HPP

namespace NFTM {
    
    char *AbsPath(char *path);
    char *LoadFile(const char *fileName, bool trimTrailingNewLine);
    char *StrCat(const char *s1, const char *s2);
    char *StrCat(const char *s1, const char *s2, const char *s3);
    char *StrCat(const char *s1, const char *s2, const char *s3, const char *s4);
    bool  StrCmp(const char *s1, const char *s2);
    char *StrDup(const char *str);
    char *StrDup(const char *str, int length);
    char *StrCopy(char *s1, const char *s2);
    char *StrCopy(char *s1, const char *s2, int maxLength);
    
} // namespace NFTM

namespace StaticCMS {

    char *LoadFile(const char *fileName);
    bool  OptIs(const char *opt, const char *is);

} // namespace StaticCMS

#endif // NFTM_static_src_bin_static_lib_nftm_Util_HPP
