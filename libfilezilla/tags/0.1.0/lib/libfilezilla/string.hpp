#ifndef LIBFILEZILLA_STRING_HEADER
#define LIBFILEZILLA_STRING_HEADER

#include "libfilezilla.hpp"

#include <string>

/** \file
 * \brief String types and assorted functions.
 *
 * Defines the \ref fz::native_string type and offers various functions to convert between
 * different string types.
 */

namespace fz {

/** \typedef native_string
 *
 * \brief A string in the system's native character type and encoding.\n Note: This typedef changes depending on platform!
 *
 * On Windows, the system's native encoding is UTF-16, so native_string is typedef'ed to std::wstring.
 *
 * On all other platform, native_string is a typedef for std::string.
 *
 * Always using native_string has the benefit that no conversion needs to be performed which is especially useful
 * if dealing with filenames.
 */

#ifdef FZ_WINDOWS
	typedef std::wstring native_string;
#endif
#if defined(FZ_UNIX) || defined(FZ_MAC)
	typedef std::string native_string;
#endif

/** \brief Converts std::string to native_string.
 *
 * \return the converted string on success. On failure an empty string is returned.
 */
native_string FZ_PUBLIC_SYMBOL to_native(std::string const& in);

/** \brief Convert std::wstring to native_string.
 *
 * \return the converted string on success. On failure an empty string is returned.
 */
native_string FZ_PUBLIC_SYMBOL to_native(std::wstring const& in);

/** \brief Locale-sensitive stricmp
 *
 * Like std::string::strcmp but case-insensitive, respectinge locale.
 *
 * \note does not handle embedded null
 */
int FZ_PUBLIC_SYMBOL stricmp(std::string const& a, std::string const& b);
int FZ_PUBLIC_SYMBOL stricmp(std::wstring const& a, std::wstring const& b);

/** \brief Converts ASCII uppercase characters to lowercase as if C-locale is used.

 Under some locales there is a different case-relationship
 between the letters a-z and A-Z as one expects from ASCII under the C locale.
 In Turkish for example there are different variations of the letter i,
 namely dotted and dotless. What we see as 'i' is the lowercase dotted i and
 'I' is the  uppercase dotless i. Since std::tolower is locale-aware, I would
 become the dotless lowercase i.

 This is not always what we want. FTP commands for example are case-insensitive
 ASCII strings, LIST and list are the same.

 tolower_ascii instead converts all types of 'i's to the ASCII i as well.

 \return  A-Z becomes a-z.\n In addition dotless lowercase i and dotted uppercase i also become the standard i.

 */
template<typename Char>
Char tolower_ascii(Char c) {
	if (c >= 'A' && c <= 'Z') {
		return c + ('a' - 'A');
	}
	return c;
}

template<>
std::wstring::value_type FZ_PUBLIC_SYMBOL tolower_ascii(std::wstring::value_type c);

/** \brief tr_tolower_ascii does for strings what tolower_ascii does for individual characters
 */
// Note: For UTF-8 strings it works on individual octets!
template<typename String>
String str_tolower_ascii(String const& s)
{
	String ret = s;
	for (auto& c : ret) {
		c = tolower_ascii(c);
	}
	return ret;
}

/** \brief Converts from std::string in system encoding into std::wstring
 *
 * \return the converted string on success. On failure an empty string is returned.
 *
 * \note Does not handle embedded nulls
 */
std::wstring FZ_PUBLIC_SYMBOL to_wstring(std::string const& in);

/// Returns identity, that way to_wstring can be called with native_string.
inline std::wstring FZ_PUBLIC_SYMBOL to_wstring(std::wstring const& in) { return in; }

/** \brief Converts from std::string in UTF-8 into std::wstring
 *
 * \return the converted string on success. On failure an empty string is returned.
 */
std::wstring FZ_PUBLIC_SYMBOL to_wstring_from_utf8(std::string const& in);

/** \brief Converts from std::wstring into std::string in system encoding
 *
 * \return the converted string on success. On failure an empty string is returned.
 *
 * \note Does not handle embedded nulls
 */
std::string FZ_PUBLIC_SYMBOL to_string(std::wstring const& in);

/// Returns identity, that way to_string can be called with native_string.
inline std::string FZ_PUBLIC_SYMBOL to_string(std::string const& in) { return in; }

/// Returns length of 0-terminated character sequence. Works with both narrow and wide-characters.
template<typename Char>
size_t strlen(Char const* str) {
	return std::char_traits<Char>::length(str);
}
}

#if !defined(fzT) || defined(DOXYGEN)
#ifdef FZ_WINDOWS
/** \brief Macro for a string literal in system-native character type.\n Note: Macro definition changes depending on platform!
 *
 * Example: \c fzT("this string is wide on Windows and narrow elsewhere")
 */
#define fzT(x) L ## x
#else
/** \brief Macro for a string literal in system-native character type.\n Note: Macro definition changes depending on platform!
 *
 * Example: \c fzT("this string is wide on Windows and narrow elsewhere")
 */
#define fzT(x) x
#endif
#endif

#endif
