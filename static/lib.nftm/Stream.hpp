#ifndef   NFTM_static_src_bin_static_Stream_HPP
#define   NFTM_static_src_bin_static_Stream_HPP

namespace NFTM {

class InputStream {
public:
	InputStream(const char *fileName);
	~InputStream();

	bool        Close(void);
	const char *ErrorMessage(void) const { return errmsg; }
	bool        IsValid(void) const { return errmsg ? false : true; }
	bool        Open(const char *fileName);
	bool        Redirect(const char *fileName);

	void       *data;
	const char *errmsg;
}; // class InputStream

class OutputStream {
public:
	OutputStream(const char *fileName);
	OutputStream(class Text *fileName);
	~OutputStream();

	bool        Close(void);
	class Text *ErrorMessage(void) const { return errmsg; }
	bool        Flush(void);
	bool        IsValid(void) const { return errmsg ? false : true; }
	bool        LogVar(class Variable *var);
	bool        Open(class Text *fileName);
	bool        Redirect(class Text *fileName);
	bool        Write(const char *fmt, ...);

    class Text *fileName;
	void       *data;
	class Text *errmsg;
}; // class OutputStream

} // namespace NFTM

#endif // NFTM_static_src_bin_static_Stream_HPP
