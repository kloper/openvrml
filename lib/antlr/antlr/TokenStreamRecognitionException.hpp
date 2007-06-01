#ifndef INC_TokenStreamRecognitionException_hpp__
#define INC_TokenStreamRecognitionException_hpp__

/* ANTLR Translator Generator
 * Project led by Terence Parr at http://www.jGuru.com
 * Software rights: http://www.antlr.org/license.html
 *
 * $Id: TokenStreamRecognitionException.hpp,v 1.1.1.4 2007-06-01 18:48:38 braden Exp $
 */

#include <antlr/config.hpp>
#include <antlr/TokenStreamException.hpp>

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
namespace antlr {
#endif

/** Exception thrown from generated lexers when there's no default error
 * handler specified.
 * @see TokenStream
 */
class TokenStreamRecognitionException : public TokenStreamException {
public:
	TokenStreamRecognitionException(RecognitionException& re)
	: TokenStreamException(re.getMessage())
	, recog(re)
	{
	}
	virtual ~TokenStreamRecognitionException() throw()
	{
	}
	virtual ANTLR_USE_NAMESPACE(std)string toString() const
	{
		return recog.getFileLineColumnString()+getMessage();
	}

	virtual ANTLR_USE_NAMESPACE(std)string getFilename() const throw()
	{
		return recog.getFilename();
	}
	virtual int getLine() const throw()
	{
		return recog.getLine();
	}
	virtual int getColumn() const throw()
	{
		return recog.getColumn();
	}
private:
	RecognitionException recog;
};

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
}
#endif

#endif //INC_TokenStreamRecognitionException_hpp__
