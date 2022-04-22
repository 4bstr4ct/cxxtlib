/*******************************************************************************
 * @file format.hpp
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Contains all format module code and functions.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef CXXTLIB_INCLUDE_CXXTLIB_FORMAT_FORMAT_HPP
#define CXXTLIB_INCLUDE_CXXTLIB_FORMAT_FORMAT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#	pragma once
#endif

#include <stdio.h>
#include <vector>

#ifndef CXXTLIB_CLANG_VERSION
#	ifndef CXXTLIB_FORMAT_CLANG_VERSION
#		if defined(__clang__) && !defined(__ibmxl__)
#			define CXXTLIB_FORMAT_CLANG_VERSION (__clang_major__ * 100 + __clang_minor__)
#		else
#			define CXXTLIB_FORMAT_CLANG_VERSION 0
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_CLANG_VERSION CXXTLIB_CLANG_VERSION
#endif

#ifndef CXXTLIB_GCC_VERSION
#	ifndef CXXTLIB_FORMAT_GCC_VERSION
#		if defined(__GNUC__) && !defined(__clang__) && !defined(__INTEL_COMPILER) && !defined(__NVCOMPILER)
#			define CXXTLIB_FORMAT_GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
#		else
#			define CXXTLIB_FORMAT_GCC_VERSION 0
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_GCC_VERSION CXXTLIB_GCC_VERSION
#endif

#ifndef CXXTLIB_GCC_PRAGMA
#	ifndef CXXTLIB_FORMAT_GCC_PRAGMA
#		if CXXTLIB_FORMAT_GCC_VERSION >= 504
#			define CXXTLIB_FORMAT_GCC_PRAGMA(arg) _Pragma(arg)
#		else
#			define CXXTLIB_FORMAT_GCC_PRAGMA(arg)
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_GCC_PRAGMA CXXTLIB_GCC_PRAGMA
#endif

#ifndef CXXTLIB_ICC_VERSION
#	ifndef CXXTLIB_FORMAT_ICC_VERSION
#		ifdef __ICL
#			define CXXTLIB_FORMAT_ICC_VERSION __ICL
#		elif defined(__INTEL_COMPILER)
#			define CXXTLIB_FORMAT_ICC_VERSION __INTEL_COMPILER
#		else
#			define CXXTLIB_FORMAT_ICC_VERSION 0
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_ICC_VERSION CXXTLIB_ICC_VERSION
#endif

#ifndef CXXTLIB_NVCOMPILER_VERSION
#	ifndef CXXTLIB_FORMAT_NVCOMPILER_VERSION
#		ifdef __NVCOMPILER
#			define CXXTLIB_FORMAT_NVCOMPILER_VERSION (__NVCOMPILER_MAJOR__ * 100 + __NVCOMPILER_MINOR__)
#		else
#			define CXXTLIB_FORMAT_NVCOMPILER_VERSION 0
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_NVCOMPILER_VERSION CXXTLIB_NVCOMPILER_VERSION
#endif

#ifndef CXXTLIB_NVCC
#	ifndef CXXTLIB_FORMAT_NVCC
#		ifdef __NVCC__
#			define CXXTLIB_FORMAT_NVCC __NVCC__
#		else
#			define CXXTLIB_FORMAT_NVCC 0
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_NVCC CXXTLIB_NVCC
#endif

#ifndef CXXTLIB_MSC_VER
#	ifndef CXXTLIB_FORMAT_MSC_VER
#		ifdef _MSC_VER
#			define CXXTLIB_FORMAT_MSC_VER _MSC_VER
#		else
#			define CXXTLIB_FORMAT_MSC_VER 0
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_MSC_VER CXXTLIB_MSC_VER
#endif

#ifndef CXXTLIB_MSC_WARNING
#	ifndef CXXTLIB_FORMAT_MSC_WARNING
#		ifdef _MSC_VER
#			define CXXTLIB_FORMAT_MSC_WARNING(...) __pragma(warning(__VA_ARGS__))
#		else
#			define CXXTLIB_FORMAT_MSC_WARNING(...)
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_MSC_WARNING CXXTLIB_MSC_WARNING
#endif

#ifndef CXXTLIB_HAS_FEATURE
#	ifndef CXXTLIB_FORMAT_HAS_FEATURE
#		ifdef __has_feature
#			define CXXTLIB_FORMAT_HAS_FEATURE(x) __has_feature(x)
#		else
#			define CXXTLIB_FORMAT_HAS_FEATURE(x) 0
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_HAS_FEATURE CXXTLIB_HAS_FEATURE
#endif

#ifndef CXXTLIB_CPLUSPLUS
#	ifndef CXXTLIB_FORMAT_CPLUSPLUS
#		ifdef _MSVC_LANG
#			define CXXTLIB_FORMAT_CPLUSPLUS _MSVC_LANG
#		else
#			define CXXTLIB_FORMAT_CPLUSPLUS __cplusplus
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_CPLUSPLUS CXXTLIB_CPLUSPLUS
#endif

#ifndef CXXTLIB_HAS_CPP_ATTRIBUTE
#	ifndef CXXTLIB_FORMAT_HAS_CPP_ATTRIBUTE
#		ifdef __has_cpp_attribute
#			define CXXTLIB_FORMAT_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#		else
#			define CXXTLIB_FORMAT_HAS_CPP_ATTRIBUTE(x) 0
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_HAS_CPP_ATTRIBUTE CXXTLIB_HAS_CPP_ATTRIBUTE
#endif

#ifndef CXXTLIB_HAS_CPP14_ATTRIBUTE
#	ifndef CXXTLIB_FORMAT_HAS_CPP14_ATTRIBUTE
#		define CXXTLIB_FORMAT_HAS_CPP14_ATTRIBUTE(attribute) (CXXTLIB_FORMAT_CPLUSPLUS >= 201402L && CXXTLIB_FORMAT_HAS_CPP_ATTRIBUTE(attribute))
#	endif
#else
#	define CXXTLIB_FORMAT_HAS_CPP14_ATTRIBUTE CXXTLIB_HAS_CPP14_ATTRIBUTE
#endif

#ifndef CXXTLIB_HAS_CPP17_ATTRIBUTE
#	ifndef CXXTLIB_FORMAT_HAS_CPP17_ATTRIBUTE
#		define CXXTLIB_FORMAT_HAS_CPP17_ATTRIBUTE(attribute) (CXXTLIB_FORMAT_CPLUSPLUS >= 201703L && CXXTLIB_FORMAT_HAS_CPP_ATTRIBUTE(attribute))
#	endif
#else
#	define CXXTLIB_FORMAT_HAS_CPP17_ATTRIBUTE CXXTLIB_HAS_CPP17_ATTRIBUTE
#endif

#ifndef CXXTLIB_MOVE_SEMANTICS_ENABLED
#	ifndef CXXTLIB_FORMAT_MOVE_SEMANTICS_ENABLED
#		if defined(CXXTLIB_FORMAT_CLANG_VERSION)
#			if CXXTLIB_FORMAT_HAS_FEATURE(__cxx_rvalue_references__)
#				define CXXTLIB_FORMAT_MOVE_SEMANTICS_ENABLED 1
#			endif
#		endif
#		if defined(__GNUC__)
#			if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 8)) || (__GNUC__ > 4)
#				if (CXXTLIB_FORMAT_CPLUSPLUS >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#					define CXXTLIB_FORMAT_MOVE_SEMANTICS_ENABLED 1
#				endif
#			endif
#		endif
#		if defined(CXXTLIB_FORMAT_MSC_VER) && (CXXTLIB_FORMAT_MSC_VER >= 1700)
#			define CXXTLIB_FORMAT_MOVE_SEMANTICS_ENABLED 1
#		endif
#		if defined(__INTEL_CXX11_MODE__)
#			if defined(CXXTLIB_FORMAT_ICC_VERSION) && (CXXTLIB_FORMAT_ICC_VERSION >= 1500)
#				define CXXTLIB_FORMAT_MOVE_SEMANTICS_ENABLED 1
#			endif
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_MOVE_SEMANTICS_ENABLED CXXTLIB_MOVE_SEMANTICS_ENABLED
#endif

#ifndef CXXTLIB_USE_CONSTEXPR
#	ifndef CXXTLIB_FORMAT_USE_CONSTEXPR
#		define CXXTLIB_FORMAT_USE_CONSTEXPR (CXXTLIB_FORMAT_HAS_FEATURE(cxx_relaxed_constexpr) || CXXTLIB_FORMAT_MSC_VER >= 1912 || (CXXTLIB_FORMAT_GCC_VERSION >= 600 && __cplusplus >= 201402L)) && !CXXTLIB_FORMAT_NVCC && !CXXTLIB_FORMAT_ICC_VERSION
#	endif
#else
#	define CXXTLIB_FORMAT_USE_CONSTEXPR CXXTLIB_USE_CONSTEXPR
#endif

#ifndef CXXTLIB_USE_CONSTEXPR
#	ifdef CXXTLIB_FORMAT_USE_CONSTEXPR
#		if CXXTLIB_FORMAT_USE_CONSTEXPR
#			define CXXTLIB_FORMAT_CONSTEXPR constexpr
#			define CXXTLIB_FORMAT_CONSTEXPR_DECL constexpr
#		else
#			define CXXTLIB_FORMAT_CONSTEXPR
#			define CXXTLIB_FORMAT_CONSTEXPR_DECL
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_USE_CONSTEXPR CXXTLIB_USE_CONSTEXPR
#	if CXXTLIB_USE_CONSTEXPR
#		define CXXTLIB_FORMAT_CONSTEXPR CXXTLIB_CONSTEXPR
#		define CXXTLIB_FORMAT_CONSTEXPR_DECL CXXTLIB_CONSTEXPR_DECL
#	else
#		define CXXTLIB_FORMAT_CONSTEXPR
#		define CXXTLIB_FORMAT_CONSTEXPR_DECL
#	endif
#endif

#ifndef CXXTLIB_NOEXCEPT
#	ifndef CXXTLIB_FORMAT_NOEXCEPT
#		if defined(_MSC_VER) && (_MSC_VER < 1900)
#			define CXXTLIB_FORMAT_NOEXCEPT _NOEXCEPT
#		else
#			define CXXTLIB_FORMAT_NOEXCEPT noexcept
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_NOEXCEPT CXXTLIB_NOEXCEPT
#endif

#ifndef CXXTLIB_INLINE
#	ifndef CXXTLIB_FORMAT_INLINE
#	 	if CXXTLIB_FORMAT_GCC_VERSION || CXXTLIB_FORMAT_CLANG_VERSION
#			define CXXTLIB_FORMAT_INLINE inline __attribute__((always_inline))
#		else
#			define CXXTLIB_FORMAT_INLINE inline
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_INLINE CXXTLIB_INLINE
#endif

#ifndef CXXTLIB_NOINLINE
#	ifndef CXXTLIB_FORMAT_NOINLINE
#		if CXXTLIB_FORMAT_GCC_VERSION || CXXTLIB_FORMAT_CLANG_VERSION
#			define CXXTLIB_FORMAT_NOINLINE __attribute__((noinline))
#		else
#			define CXXTLIB_FORMAT_NOINLINE
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_NOINLINE CXXTLIB_NOINLINE
#endif

#ifndef CXXTLIB_NORETURN
#	ifndef CXXTLIB_FORMAT_NORETURN
#		if CXXTLIB_FORMAT_EXCEPTIONS && CXXTLIB_FORMAT_HAS_CPP_ATTRIBUTE(noreturn) && !CXXTLIB_FORMAT_MSC_VER && !CXXTLIB_FORMAT_NVCC
#			define CXXTLIB_FORMAT_NORETURN [[noreturn]]
#		else
#			define CXXTLIB_FORMAT_NORETURN
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_NORETURN CXXTLIB_NORETURN
#endif

#ifndef CXXTLIB_NODISCARD
#	ifndef CXXTLIB_FORMAT_NODISCARD
#		if CXXTLIB_FORMAT_HAS_CPP17_ATTRIBUTE(nodiscard)
#			define CXXTLIB_FORMAT_NODISCARD [[nodiscard]]
#		else
#			define CXXTLIB_FORMAT_NODISCARD
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_NODISCARD CXXTLIB_NODISCARD
#endif

#ifndef CXXTLIB_DEPRECATED
#	ifndef CXXTLIB_FORMAT_DEPRECATED
#		if CXXTLIB_FORMAT_HAS_CPP14_ATTRIBUTE(deprecated) || CXXTLIB_FORMAT_MSC_VER >= 1900
#			define CXXTLIB_FORMAT_DEPRECATED [[deprecated]]
#		else
#			if (defined(__GNUC__) && !defined(__LCC__)) || defined(__clang__)
#				define CXXTLIB_FORMAT_DEPRECATED __attribute__((deprecated))
#			elif CXXTLIB_FORMAT_MSC_VER
#				define CXXTLIB_FORMAT_DEPRECATED __declspec(deprecated)
#			else
#				define CXXTLIB_FORMAT_DEPRECATED /* deprecated */
#			endif
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_DEPRECATED CXXTLIB_DEPRECATED
#endif

#ifndef CXXTLIB_DEBUG
#	ifndef CXXTLIB_FORMAT_DEBUG
#		if _MSC_VER
#			define CXXTLIB_FORMAT_DEBUG _DEBUG
#		else
#			define CXXTLIB_FORMAT_DEBUG NDEBUG
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_DEBUG CXXTLIB_DEBUG
#endif

#ifndef CXXTLIB_OS
#	ifndef CXXTLIB_FORMAT_OS
#		ifndef CXXTLIB_FORMAT_OS_WINDOWS
#			if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#				define CXXTLIB_FORMAT_OS_WINDOWS 1
#				define CXXTLIB_FORMAT_OS CXXTLIB_FORMAT_OS_WINDOWS
#			endif
#			ifdef _WIN64
#				define CXXTLIB_FORMAT_OS_WINDOWS_X64 1
#			else
#				define CXXTLIB_FORMAT_OS_WINDOWS_X32 1
#			endif
#		endif
#		ifndef CXXTLIB_FORMAT_OS_LINUX
#			if __linux__
#				define CXXTLIB_FORMAT_OS_LINUX 1
#				define CXXTLIB_FORMAT_OS CXXTLIB_FORMAT_OS_LINUX
#			endif
#		endif
#		ifndef CXXTLIB_FORMAT_OS_MACOS
#			if __APPLE__
#				define CXXTLIB_FORMAT_OS_MACOS 1
#				define CXXTLIB_FORMAT_OS CXXTLIB_FORMAT_OS_MACOS
#			endif
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_OS CXXTLIB_OS
#	ifdef CXXTLIB_OS_WINDOWS
#		define CXXTLIB_FORMAT_OS_WINDOWS CXXTLIB_OS_WINDOWS
#	else
#		define CXXTLIB_FORMAT_OS_WINDOWS
#	endif
#	ifdef CXXTLIB_OS_LINUX
#		define CXXTLIB_FORMAT_OS_LINUX CXXTLIB_OS_LINUX
#	else
#		define CXXTLIB_FORMAT_OS_LINUX
#	endif
#	ifdef CXXTLIB_OS_MACOS
#		define CXXTLIB_FORMAT_OS_MACOS CXXTLIB_OS_MACOS
#	else
#		define CXXTLIB_FORMAT_OS_MACOS
#	endif
#endif

#ifndef CXXTLIB_ALIAS
#	ifndef CXXTLIB_FORMAT_ALIAS
#		if CXXTLIB_FORMAT_CPLUSPLUS < 201103L
#			define CXXTLIB_FORMAT_ALIAS(type, alias) typedef type alias
#		else
#			define CXXTLIB_FORMAT_ALIAS(type, alias) using alias = type
#		endif
#	endif
#else
#	define CXXTLIB_FORMAT_ALIAS(type, alias) CXXTLIB_ALIAS(type, alias)
#endif

#ifndef CXXTLIB_COMMA
#	ifndef CXXTLIB_FORMAT_COMMA
#		define CXXTLIB_FORMAT_COMMA ,
#	endif
#else
#	define CXXTLIB_FORMAT_COMMA CXXTLIB_COMMA
#endif

#ifndef COMMA
#	if defined(CXXTLIB_COMMA)
#		define COMMA CXXTLIB_COMMA
#	elif defined(CXXTLIB_FORMAT_COMMA)
#		define COMMA CXXTLIB_FORMAT_COMMA
#	else
#		define COMMA ,
#	endif
#endif

namespace cxxtlib
{
	namespace format
	{
		namespace details
		{
			/**
			 * A type represeting null.
			 */
			CXXTLIB_FORMAT_ALIAS(decltype(nullptr), null);

			/**
			 * A type representing signed char.
			 */
			CXXTLIB_FORMAT_ALIAS(signed char, int8);

			/**
			 * A type representing unsigned char.
			 */
			CXXTLIB_FORMAT_ALIAS(unsigned char, uint8);
			
			/**
			 * A type representing unsigned char.
			 */
			CXXTLIB_FORMAT_ALIAS(unsigned char, byte);

			/**
			 * A type representing signed short.
			 */
			CXXTLIB_FORMAT_ALIAS(signed short, int16);

			/**
			 * A type representing unsigned short.
			 */
			CXXTLIB_FORMAT_ALIAS(unsigned short, uint16);

			/**
			 * A type representing signed int.
			 */
			CXXTLIB_FORMAT_ALIAS(signed int, int32);
			
			/**
			 * A type representing unsigned int.
			 */
			CXXTLIB_FORMAT_ALIAS(unsigned int, uint32);

			/**
			 * A type representing signed long long.
			 */
			CXXTLIB_FORMAT_ALIAS(signed long long, int64);
			
			/**
			 * A type representing unsigned long long.
			 */
			CXXTLIB_FORMAT_ALIAS(unsigned long long, uint64);

			/**
			 * A type representing long double.
			 */
			CXXTLIB_FORMAT_ALIAS(long double, ldouble);

			/**
			 * A type representing wide char.
			 */
			CXXTLIB_FORMAT_ALIAS(wchar_t, wchar);

				template<typename Char>
			struct FormatTraits;

			template<>
			struct FormatTraits<char>
			{
			public:
				static CXXTLIB_FORMAT_CONSTEXPR const char baseSpecifier = 'b';
				static CXXTLIB_FORMAT_CONSTEXPR const char decimalBaseSpecifier = 'd';
				static CXXTLIB_FORMAT_CONSTEXPR const char hexadecimalBaseSpecifier = 'x';
				static CXXTLIB_FORMAT_CONSTEXPR const char octalBaseSpecifier = 'o';

				static CXXTLIB_FORMAT_CONSTEXPR const char precisionSpecifier = 'p';

				static CXXTLIB_FORMAT_CONSTEXPR const char columnSpecifier = ':';
				static CXXTLIB_FORMAT_CONSTEXPR const char terminationSpecifier = '\0';
				static CXXTLIB_FORMAT_CONSTEXPR const char spaceSpecifier = ' ';
				static CXXTLIB_FORMAT_CONSTEXPR const char endLineSpecifier = '\n';

				static CXXTLIB_FORMAT_CONSTEXPR const char percentageSpecifier = '%';
				static CXXTLIB_FORMAT_CONSTEXPR const char leftSquareBracketSpecifier = '[';
				static CXXTLIB_FORMAT_CONSTEXPR const char rightSquareBracketSpecifier = ']';
				static CXXTLIB_FORMAT_CONSTEXPR const char leftCurlyBracketSpecifier = '{';
				static CXXTLIB_FORMAT_CONSTEXPR const char rightCurlyBracketSpecifier = '}';

				static CXXTLIB_FORMAT_CONSTEXPR const char trueStringified[] = "true";
				static CXXTLIB_FORMAT_CONSTEXPR const char falseStringified[] = "false";
				static CXXTLIB_FORMAT_CONSTEXPR const char nullptrStringified[] = "nullptr";
			};
			
			template<>
			struct FormatTraits<details::wchar>
			{
			public:
				static CXXTLIB_FORMAT_CONSTEXPR const details::wchar baseSpecifier = L'b';
				static CXXTLIB_FORMAT_CONSTEXPR const details::wchar decimalBaseSpecifier = L'd';
				static CXXTLIB_FORMAT_CONSTEXPR const details::wchar hexadecimalBaseSpecifier = L'x';
				static CXXTLIB_FORMAT_CONSTEXPR const details::wchar octalBaseSpecifier = L'o';

				static CXXTLIB_FORMAT_CONSTEXPR const details::wchar precisionSpecifier = L'p';

				static CXXTLIB_FORMAT_CONSTEXPR const details::wchar percentageSpecifier = L'%';
				static CXXTLIB_FORMAT_CONSTEXPR const details::wchar columnSpecifier = L':';
				static CXXTLIB_FORMAT_CONSTEXPR const details::wchar terminationSpecifier = L'\0';
				static CXXTLIB_FORMAT_CONSTEXPR const details::wchar spaceSpecifier = L' ';
				static CXXTLIB_FORMAT_CONSTEXPR const details::wchar endLineSpecifier = L'\n';

				static CXXTLIB_FORMAT_CONSTEXPR const details::wchar leftSquareBracketSpecifier = L'[';
				static CXXTLIB_FORMAT_CONSTEXPR const details::wchar rightSquareBracketSpecifier = L']';
				static CXXTLIB_FORMAT_CONSTEXPR const details::wchar leftCurlyBracketSpecifier = L'{';
				static CXXTLIB_FORMAT_CONSTEXPR const details::wchar rightCurlyBracketSpecifier = L'}';

				static CXXTLIB_FORMAT_CONSTEXPR const details::wchar trueStringified[] = L"true";
				static CXXTLIB_FORMAT_CONSTEXPR const details::wchar falseStringified[] = L"false";
				static CXXTLIB_FORMAT_CONSTEXPR const details::wchar nullptrStringified[] = L"nullptr";
			};

			namespace ascii
			{
				static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR uint32 length(const char* pString) CXXTLIB_FORMAT_NOEXCEPT
				{
					uint32 count = 0;
					while (pString[count]) count++;
					return count;
				}

				template<typename Char>
				static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR uint32 length(const Char* pString) CXXTLIB_FORMAT_NOEXCEPT
				{
					uint32 count = 0;
					while (pString[count] != FormatTraits<Char>::terminationSpecifier) count++;
					return count;
				}

				static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR char* copy(char* destination, const char* source) CXXTLIB_FORMAT_NOEXCEPT
				{
					char* head = destination;
					while((*destination++ = *source++) != '\0');
					return head;
				}

				template<typename Char>
				static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR Char* copy(Char* destination, const Char* source) CXXTLIB_FORMAT_NOEXCEPT
				{
					Char* head = destination;
					while((*destination++ = *source++) != FormatTraits<Char>::terminationSpecifier);
					return head;
				}

				static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR char* copy(char* destination, const char* source, uint32 pCount) CXXTLIB_FORMAT_NOEXCEPT
				{
					char* head = destination;
					for (uint32 index = 0; index < pCount; index++) destination[index] = source[index];
					return head;
				}

				template<typename Char>
				static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR Char* copy(Char* destination, const Char* source, uint32 pCount) CXXTLIB_FORMAT_NOEXCEPT
				{
					Char* head = destination;
					for (uint32 index = 0; index < pCount; index++) destination[index] = source[index];
					return head;
				}

				static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void reverse(char* pString) CXXTLIB_FORMAT_NOEXCEPT
				{
					uint32 size = length((const char*)pString);
					
					for (int32 i = 0, j = size - 1; i < j; i++, j--)
					{
						char a = pString[i];
						pString[i] = pString[j];
						pString[j] = a;
					}
				}

				template<typename Char>
				static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void reverse(Char* pString) CXXTLIB_FORMAT_NOEXCEPT
				{
					uint32 size = length((const Char*)pString);
					
					for (int32 i = 0, j = size - 1; i < j; i++, j--)
					{
						Char a = pString[i];
						pString[i] = pString[j];
						pString[j] = a;
					}
				}
			}

			// Add constant
			template<typename Type>
			struct AddConst
			{
			public:
				CXXTLIB_FORMAT_ALIAS(const Type, ValueType);
			};

			// Remove constant
			template<typename Type>
			struct RemoveConst
			{
			public:
				CXXTLIB_FORMAT_ALIAS(Type, ValueType);
			};
			
			template<typename Type>
			struct RemoveConst<const Type>
			{
			public:
				CXXTLIB_FORMAT_ALIAS(Type, ValueType);
			};

			// Add volatile
			template<typename Type>
			struct AddVolatile
			{
			public:
				CXXTLIB_FORMAT_ALIAS(volatile Type, ValueType);
			};
			
			// Remove volatile
			template<typename Type>
			struct RemoveVolatile
			{
			public:
				CXXTLIB_FORMAT_ALIAS(Type, ValueType);
			};

			template<typename Type>
			struct RemoveVolatile<volatile Type>
			{
			public:
				CXXTLIB_FORMAT_ALIAS(Type, ValueType);
			};

			// Add constant volatile
			template<typename Type>
			struct AddConstVolatile
			{
			public:
				CXXTLIB_FORMAT_ALIAS(typename AddConst<typename AddVolatile<Type>::ValueType>::ValueType, ValueType);
			};

			// Remove constant volatile
			template<typename Type>
			struct RemoveConstVolatile
			{
			public:
				CXXTLIB_FORMAT_ALIAS(typename RemoveConst<typename RemoveVolatile<Type>::ValueType>::ValueType, ValueType);
			};

			// Remove reference
			template<typename Type>
			struct RemoveReference
			{
			public:
				CXXTLIB_FORMAT_ALIAS(Type, ValueType);
			};
			
			template<typename Type>
			struct RemoveReference<Type&>
			{
			public:
				CXXTLIB_FORMAT_ALIAS(Type, ValueType);
			};

			template<typename Type>
			struct RemoveReference<Type&&>
			{
			public:
				CXXTLIB_FORMAT_ALIAS(Type, ValueType);
			};

			// Integral constant
			template<typename Type, Type tValue>
			struct IntegralConstant
			{
			public:
				CXXTLIB_FORMAT_ALIAS(Type, ValueType);

			public:
				static CXXTLIB_FORMAT_CONSTEXPR const Type value = tValue;
			};

			// Boolean
#if CXXTLIB_FORMAT_CPLUSPLUS < 201103L
			template<bool tValue>
			struct BoolConstant : public IntegralConstant<bool, tValue>
			{ };
#else
			template<bool tValue>
			CXXTLIB_FORMAT_ALIAS(IntegralConstant<bool COMMA tValue>, BoolConstant);
#endif

			CXXTLIB_FORMAT_ALIAS(IntegralConstant<bool COMMA true>, TrueType);

			CXXTLIB_FORMAT_ALIAS(IntegralConstant<bool COMMA false>, FalseType);

			// Meta
			template<bool, typename, typename>
			struct Conditional;

			template<typename>
			struct IsLValueReference;

			template<typename>
			struct IsRValueReference;

			// Conditional
			template<bool tCondition, typename IfTrue, typename IfFalse>
			struct Conditional
			{
			public:
				CXXTLIB_FORMAT_ALIAS(IfTrue, ValueType);
			};

			template<typename IfTrue, typename IfFalse>
			struct Conditional<false, IfTrue, IfFalse>
			{
			public:
				CXXTLIB_FORMAT_ALIAS(IfFalse, ValueType);
			};

			// Or
			template<typename...>
			struct Or;

			template<>
			struct Or<>
				: public FalseType
			{ };

			template<typename First>
			struct Or<First>
				: public First
			{ };

			template<typename First, typename Second>
			struct Or<First, Second>
				: public Conditional<First::value, First, Second>::ValueType
			{ };

			template<typename First, typename Second, typename Third, typename... Other>
			struct Or<First, Second, Third, Other...>
				: public Conditional<First::value, First, Or<Second, Third, Other...>>::ValueType
			{ };

			// And
			template<typename...>
			struct And;

			template<>
			struct And<>
				: public TrueType
			{ };

			template<typename First>
			struct And<First>
				: public First
			{ };

			template<typename First, typename Second>
			struct And<First, Second>
				: public Conditional<First::value, Second, First>::ValueType
			{ };

			template<typename First, typename Second, typename Third, typename... Other>
			struct And<First, Second, Third, Other...>
				: public Conditional<First::value, And<Second, Third, Other...>, First>::ValueType
			{ };

			// Not
			template<typename Type>
			struct Not
				: public BoolConstant<!bool(Type::value)>
			{ };

			// Identity type
			template<typename Type>
			struct Identity
			{
			public:
				CXXTLIB_FORMAT_ALIAS(Type, ValueType);
			};

			// Is constant
			template<typename>
			struct IsConst
				: public FalseType
			{ };

			template<typename Type>
			struct IsConst<const Type>
				: public TrueType
			{ };

			// Is volatile
			template<typename>
			struct IsVolatile
				: public FalseType
			{ };

			template<typename Type>
			struct IsVolatile<volatile Type>
				: public TrueType
			{ };

			// Is constant volatile
			template<typename>
			struct IsConstVolatile
				: public FalseType
			{ };

			template<typename Type>
			struct IsConstVolatile<const volatile Type>
				: public TrueType
			{ };

			// Is literal
			template<typename Type>
			struct IsLiteral
				: public IntegralConstant<bool, __is_literal_type(Type)>
			{ };

			// Is empty
			template<typename Type>
			struct IsEmpty
				: public IntegralConstant<bool, __is_empty(Type)>
			{ };

			// Is polymorphic
			template<typename Type>
			struct IsPolymorphic
				: public IntegralConstant<bool, __is_polymorphic(Type)>
			{ };

			// Is final
#if __cplusplus >= 201402L
			template<typename Type>
			struct IsFinal
				: public IntegralConstant<bool, __is_final(Type)>
			{ };
#endif
			
			// Is abstract
			template<typename Type>
			struct IsAbstract
				: public IntegralConstant<bool, __is_abstract(Type)>
			{ };

			// Is void
			template<typename>
			struct IsVoidHelper
				: public FalseType
			{ };

			template<>
			struct IsVoidHelper<void>
				: public TrueType
			{ };

			template<typename Type>
			struct IsVoid
				: public IsVoidHelper<typename RemoveConstVolatile<Type>::ValueType>
			{ };

			// Is integral
			template<typename>
			struct IsIntegralHelper
				: public FalseType
			{ };

			template<>
			struct IsIntegralHelper<bool> :
				public TrueType
			{ };

			template<>
			struct IsIntegralHelper<char> :
				public TrueType
			{ };

			template<>
			struct IsIntegralHelper<signed char>
				: public TrueType
			{ };

			template<>
			struct IsIntegralHelper<unsigned char>
				: public TrueType
			{ };

			template<>
			struct IsIntegralHelper<wchar_t>
				: public TrueType
			{ };

			template<>
			struct IsIntegralHelper<char16_t>
				: public TrueType
			{ };

			template<>
			struct IsIntegralHelper<char32_t>
				: public TrueType
			{ };

			template<>
			struct IsIntegralHelper<signed short>
				: public TrueType
			{ };

			template<>
			struct IsIntegralHelper<unsigned short>
				: public TrueType
			{ };

			template<>
			struct IsIntegralHelper<signed int>
				: public TrueType
			{ };

			template<>
			struct IsIntegralHelper<unsigned int>
				: public TrueType
			{ };

			template<>
			struct IsIntegralHelper<signed long>
				: public TrueType
			{ };

			template<>
			struct IsIntegralHelper<unsigned long>
				: public TrueType
			{ };

			template<>
			struct IsIntegralHelper<signed long long>
				: public TrueType
			{ };

			template<>
			struct IsIntegralHelper<unsigned long long>
				: public TrueType
			{ };

			template<typename Type>
			struct IsIntegral
				: public IsIntegralHelper<typename RemoveConstVolatile<Type>::ValueType>
			{ };

			// Is floating point
			template<typename>
			struct IsFloatingPointHelper
				: public FalseType
			{ };

			template<>
			struct IsFloatingPointHelper<float>
				: public TrueType
			{ };

			template<>
			struct IsFloatingPointHelper<double>
				: public TrueType
			{ };

			template<>
			struct IsFloatingPointHelper<long double>
				: public TrueType
			{ };

			template<typename Type>
			struct IsFloatingPoint
				: public IsFloatingPointHelper<typename RemoveConstVolatile<Type>::ValueType>
			{ };

			// Is array
			template<typename>
			struct IsArray
				: public FalseType
			{ };

			template<typename Type, uint32 size>
			struct IsArray<Type[size]>
				: public TrueType
			{ };

			template<typename Type>
			struct IsArray<Type[]>
				: public TrueType
			{ };

			// Is pointer
			template<typename>
			struct IsPointerHelper
				: public FalseType
			{ };

			template<typename Type>
			struct IsPointerHelper<Type*>
				: public TrueType
			{ };

			template<typename Type>
			struct IsPointer
				: public IsPointerHelper<typename RemoveConstVolatile<Type>::ValueType>
			{ };

			// Is enum
			template<typename Type>
			struct IsEnum
				: public BoolConstant<__is_enum(Type)>
			{ };

			// Is union
			template<typename Type>
			struct IsUnion
				: public BoolConstant<__is_union(Type)>
			{ };

			// Is class
			template<typename Type>
			struct IsClass
				: public BoolConstant<__is_class(Type)>
			{ };

			// Is function
			template<typename>
			struct IsFunction
				: public FalseType
			{ };

			template<typename Result, typename... Arguments>
			struct IsFunction<Result(Arguments...)>
				: public TrueType
			{ };

			template<typename Result, typename... Arguments>
			struct IsFunction<Result(Arguments...)&>
				: public TrueType
			{ };

			template<typename Result, typename... Arguments>
			struct IsFunction<Result(Arguments...)&&>
				: public TrueType
			{ };

			template<typename Result, typename... Arguments>
			struct IsFunction<const Result(Arguments...)>
				: public TrueType
			{ };

			template<typename Result, typename... Arguments>
			struct IsFunction<const Result(Arguments...)&>
				: public TrueType
			{ };

			template<typename Result, typename... Arguments>
			struct IsFunction<const Result(Arguments...)&&>
				: public TrueType
			{ };

			template<typename Result, typename... Arguments>
			struct IsFunction<volatile Result(Arguments...)>
				: public TrueType
			{ };

			template<typename Result, typename... Arguments>
			struct IsFunction<volatile Result(Arguments...)&>
				: public TrueType
			{ };

			template<typename Result, typename... Arguments>
			struct IsFunction<volatile Result(Arguments...)&&>
				: public TrueType
			{ };

			template<typename Result, typename... Arguments>
			struct IsFunction<const volatile Result(Arguments...)>
				: public TrueType
			{ };

			template<typename Result, typename... Arguments>
			struct IsFunction<const volatile Result(Arguments...)&>
				: public TrueType
			{ };

			template<typename Result, typename... Arguments>
			struct IsFunction<const volatile Result(Arguments...)&&>
				: public TrueType
			{ };

			// Is null pointer
			template<typename>
			struct IsNullPointerHelper
				: public FalseType
			{ };

			template<>
			struct IsNullPointerHelper<decltype(nullptr)>
				: public TrueType
			{ };

			template<typename Type>
			struct IsNullPointer
				: public IsNullPointerHelper<typename RemoveConstVolatile<Type>::ValueType>
			{ };

			// Is reference
			template<typename Type>
			struct IsReference
				: public Or<IsLValueReference<Type>, IsRValueReference<Type>>
			{ };

			/// Is object
			template<typename Type>
			struct IsObject
				: public Not<Or<IsFunction<Type>, IsReference<Type>, IsVoid<Type>>>
			{ };

			// Referenceable
			template<typename Type>
			struct IsReferenceable
				: public Or<IsObject<Type>, IsReference<Type>>
			{ };

			template<typename Result, typename... Arguments>
			struct IsReferenceable<Result(Arguments...)>
				: public TrueType
			{ };

			// L value
			template<typename>
			struct IsLValueReference
				: public FalseType
			{ };

			template<typename Type>
			struct IsLValueReference<Type&>
				: public TrueType
			{ };

			template<typename Type, bool = IsReferenceable<Type>::value>
			struct AddLValueReferenceHelper
			{
			public:
				CXXTLIB_FORMAT_ALIAS(Type, ValueType);
			};

			template<typename Type>
			struct AddLValueReferenceHelper<Type, true>
			{
			public:
				CXXTLIB_FORMAT_ALIAS(Type&, ValueType);
			};

			template<typename Type>
			struct AddLValueReference
				: public AddLValueReferenceHelper<Type>
			{ };

			// R value
			template<typename>
			struct IsRValueReference
				: public FalseType
			{ };

			template<typename Type>
			struct IsRValueReference<Type&&>
				: public TrueType
			{ };

			template<typename Type, bool = IsReferenceable<Type>::value>
			struct AddRValueReferenceHelper
			{
			public:
				CXXTLIB_FORMAT_ALIAS(Type, ValueType);
			};

			template<typename Type>
			struct AddRValueReferenceHelper<Type, true>
			{
			public:
				CXXTLIB_FORMAT_ALIAS(Type&&, ValueType);
			};

			template<typename Type>
			struct AddRValueReference
				: public AddRValueReferenceHelper<Type>
			{ };

			// Enable if
			template<bool, typename Type = void>
			struct EnableIf { };

			template<typename Type>
			struct EnableIf<true, Type>
			{
			public:
				CXXTLIB_FORMAT_ALIAS(Type, ValueType);
			};

			// Forward
			template<typename Type>
			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR typename EnableIf<!IsLValueReference<Type>::value, Type&&>::ValueType forward(typename Identity<Type>::ValueType& type) CXXTLIB_FORMAT_NOEXCEPT
			{
				return static_cast<Type&&>(type);
			}

			template<typename Type>
			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR typename EnableIf<!IsLValueReference<Type>::value, Type&&>::ValueType forward(typename Identity<Type>::ValueType&& type) CXXTLIB_FORMAT_NOEXCEPT
			{
				return static_cast<Type&&>(type);
			}

			template<typename Type>
			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR typename EnableIf<IsLValueReference<Type>::value, Type>::ValueType forward(typename Identity<Type>::ValueType type) CXXTLIB_FORMAT_NOEXCEPT
			{
				return type;
			}

			template<typename Type>
			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR typename EnableIf<IsLValueReference<Type>::value, Type>::ValueType forward(typename RemoveReference<Type>::ValueType&& type) CXXTLIB_FORMAT_NOEXCEPT = delete;

			// Move
			template<typename Type>
			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR typename RemoveReference<Type>::ValueType&& move(Type&& type) CXXTLIB_FORMAT_NOEXCEPT
			{
				return static_cast<typename RemoveReference<Type>::ValueType&&>(type);
			}
		}

		/**
		 * Defines types of format arguments.
		 */
		enum class FormatArgumentType : details::uint8
		{
			None,
			Bool,
			Char,
			Int8,
			UInt8,
			Int16,
			UInt16,
			Int32,
			UInt32,
			Int64,
			UInt64,
			Float,
			Double,
			LDouble,
			Pointer,
			Array,
			CString,
			Custom
		};

		template<typename Type>
		struct TypeOf
		{
		public:
			static CXXTLIB_FORMAT_CONSTEXPR const FormatArgumentType value = FormatArgumentType::None;
		};

		#define NONE

		#define __struct_INTERNAL_TYPE_OF(DTypes, Type, FType) \
		template<DTypes> \
		struct TypeOf<Type> \
		{ \
		public: \
			static CXXTLIB_FORMAT_CONSTEXPR const FormatArgumentType value = FType; \
		}

		__struct_INTERNAL_TYPE_OF(NONE, bool, FormatArgumentType::Bool);
		__struct_INTERNAL_TYPE_OF(NONE, char, FormatArgumentType::Char);
		__struct_INTERNAL_TYPE_OF(NONE, details::int8, FormatArgumentType::Int8);
		__struct_INTERNAL_TYPE_OF(NONE, details::uint8, FormatArgumentType::UInt8);
		__struct_INTERNAL_TYPE_OF(NONE, details::int16, FormatArgumentType::Int16);
		__struct_INTERNAL_TYPE_OF(NONE, details::uint16, FormatArgumentType::UInt16);
		__struct_INTERNAL_TYPE_OF(NONE, details::int32, FormatArgumentType::Int32);
		__struct_INTERNAL_TYPE_OF(NONE, details::uint32, FormatArgumentType::UInt32);
		__struct_INTERNAL_TYPE_OF(NONE, details::int64, FormatArgumentType::Int64);
		__struct_INTERNAL_TYPE_OF(NONE, details::uint64, FormatArgumentType::UInt64);
		__struct_INTERNAL_TYPE_OF(NONE, float, FormatArgumentType::Float);
		__struct_INTERNAL_TYPE_OF(NONE, double, FormatArgumentType::Double);
		__struct_INTERNAL_TYPE_OF(NONE, details::ldouble, FormatArgumentType::LDouble);
		__struct_INTERNAL_TYPE_OF(typename Type, Type*, FormatArgumentType::Pointer);
		__struct_INTERNAL_TYPE_OF(typename Type, const Type*, FormatArgumentType::Pointer);
		__struct_INTERNAL_TYPE_OF(NONE, details::null, FormatArgumentType::Pointer);
		__struct_INTERNAL_TYPE_OF(NONE, const char*, FormatArgumentType::CString);
		__struct_INTERNAL_TYPE_OF(NONE, const char[], FormatArgumentType::CString);
		__struct_INTERNAL_TYPE_OF(typename details::uint32 tSize, const char[tSize], FormatArgumentType::CString);
		
		template<typename Char>
		struct FormatterHelpers
		{
		public:
			template<typename Context>
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parseIgnore(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				for (; *pContext != details::FormatTraits<Char>::rightCurlyBracketSpecifier; pContext++);
				pContext++;
			}
		};

		template<typename Char>
		struct FormatterBase
		{ };
		
		template<typename Char, typename Type, typename Enable = void>
		struct Formatter
		{
			static_assert(TypeOf<Type>::value != FormatArgumentType::None, "Provided type does not have a formatter!");
		};

		#define FormatterEnabler(Type) typename details::EnableIf \
		< \
			details::And \
			< \
				details::BoolConstant \
				< \
					details::IntegralConstant \
					< \
						FormatArgumentType, \
						TypeOf<Type>::value \
					>::value != FormatArgumentType::None \
				>, \
				details::BoolConstant \
				< \
					details::IntegralConstant \
					< \
						FormatArgumentType, \
						TypeOf<Type>::value \
					>::value != FormatArgumentType::/*None*/ Custom \
				> \
			>::value \
		>::ValueType

		struct p { };

		__struct_INTERNAL_TYPE_OF(NONE, p, FormatArgumentType::Array);

		template<typename Char, typename Type>
		struct Formatter<Char, Type, FormatterEnabler(Type)>
		{
		public:
			using ValueType = Type;
		};

		template<typename Char>
		struct Formatter<Char, p, FormatterEnabler(p)> : public FormatterBase<Char>
		{
		public:

		};

		#define __struct_INTERNAL_FORMATTER(DTypes, Type, PFunc, FFunc) \
		template<DTypes> \
		struct Formatter<Char, Type, FormatterEnabler(Type)> : public FormatterBase<Char> \
		{ \
		public: \
			template<typename Context> \
			PFunc \
			 \
			template<typename Context> \
			FFunc \
		}

		__struct_INTERNAL_FORMATTER(typename Char, bool,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers<Char>::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext, bool pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				pContext.append(
					pValue ? details::FormatTraits<Char>::trueStringified
						: details::FormatTraits<Char>::falseStringified,
					pValue ? details::ascii::length<Char>(details::FormatTraits<Char>::trueStringified)
						: details::ascii::length<Char>(details::FormatTraits<Char>::falseStringified)
				);
			}
		);

		__struct_INTERNAL_FORMATTER(typename Char, Char,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers<Char>::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext, Char pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				pContext.append(pValue);
			}
		);

		__struct_INTERNAL_FORMATTER(typename Char, details::int8,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers<Char>::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext, details::int8 pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 5u;
				Char buffer[size] { };
				const details::int32 written = ::snprintf(buffer, size, "%d", pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer, written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(typename Char, details::uint8,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers<Char>::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext, details::uint8 pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 5u;
				Char buffer[size] { };
				const details::int32 written = ::snprintf(buffer, size, "%u", pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer, written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(typename Char, details::int16,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers<Char>::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext, details::int16 pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 7u;
				Char buffer[size] { };
				const details::int32 written = ::snprintf(buffer, size, "%d", pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer, written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(typename Char, details::uint16,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers<Char>::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext, details::uint16 pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 7u;
				Char buffer[size] { };
				const details::int32 written = ::snprintf(buffer, size, "%u", pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer, written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(typename Char, details::int32,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers<Char>::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext, details::int32 pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 12u;
				Char buffer[size] { };
				const details::int32 written = ::snprintf(buffer, size, "%d", pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer, written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(typename Char, details::uint32,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers<Char>::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext, details::uint32 pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 12u;
				Char buffer[size] { };
				const details::int32 written = ::snprintf(buffer, size, "%u", pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer, written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(typename Char, details::int64,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers<Char>::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext, details::int64 pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 21u;
				Char buffer[size] { };
				const details::int32 written = ::snprintf(buffer, size, "%lld", pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer, written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(typename Char, details::uint64,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers<Char>::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext, details::uint64 pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 21u;
				Char buffer[size] { };
				const details::int32 written = ::snprintf(buffer, size, "%llu", pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer, written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(typename Char, float,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers<Char>::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext, float pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 25u;
				Char buffer[size] { };
				const details::int32 written = ::snprintf(buffer, size, "%f", pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer, written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(typename Char, double,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers<Char>::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext, double pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 25u;
				Char buffer[size] { };
				const details::int32 written = ::snprintf(buffer, size, "%f", pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer, written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(typename Char, details::ldouble,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers<Char>::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext, details::ldouble pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 26u;
				Char buffer[size] { };
				const details::int32 written = ::snprintf(buffer, size, "%Lf", pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer, written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(typename Char COMMA typename Type, Type*,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers<Char>::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext, Type* pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 19u;
				Char buffer[size] { };
				const details::int32 written = ::snprintf(buffer, size, "0x%p", (void*)pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer, written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(typename Char COMMA typename Type, const Type*,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers<Char>::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext, const Type* pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 19u;
				Char buffer[size] { };
				const details::int32 written = ::snprintf(buffer, size, "0x%p", (const void*)pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer, written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(typename Char, details::null,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers<Char>::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext, details::null pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				pContext.append(details::FormatTraits<Char>::nullptrStringified, 7u);
			}
		);

		__struct_INTERNAL_FORMATTER(typename Char, const Char*,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers<Char>::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext, const Char* pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				if (pValue)
				{
					pContext.append(pValue, details::ascii::length<Char>(pValue));
				}
				else
				{
					pContext.append(details::FormatTraits<Char>::nullptrStringified, 7u);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(typename Char, const Char[],
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers<Char>::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext, const Char pValue[]) CXXTLIB_FORMAT_NOEXCEPT
			{
				pContext.append(pValue, details::ascii::length<Char>(pValue));
			}
		);

		__struct_INTERNAL_FORMATTER(typename Char COMMA typename details::uint32 tSize, const Char[tSize],
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers<Char>::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext, const Char pValue[tSize]) CXXTLIB_FORMAT_NOEXCEPT
			{
				pContext.append(pValue, tSize - 1);
			}
		);

		template<typename Char, typename Reader, typename Writer>
		static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void formatHandle(Reader& pReader, Writer& pWriter) CXXTLIB_FORMAT_NOEXCEPT
		{
			pWriter.append(pReader.iterator(), pReader.size());
		}

		template<typename Char, typename Reader, typename Writer, typename Argument, typename... Arguments>
		static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void formatHandle(Reader& pReader, Writer& pWriter, Argument&& pArgument, Arguments&&... pArguments) CXXTLIB_FORMAT_NOEXCEPT
		{
			// Setting pointer to the beggining for this section of pattern
			const Char* previous = pReader.iterator();
			// Iterating untill next '{' character in pattern is present
			for (; *pReader != details::FormatTraits<Char>::leftCurlyBracketSpecifier && pReader.iterator() != pReader.end(); pReader++);

			if (*pReader == details::FormatTraits<Char>::leftCurlyBracketSpecifier)
			{
				// Appending text from pattern.
				pWriter.append(previous, (details::uint32)(pReader.iterator() - previous));
				// Removing references for types and volatiles.
				CXXTLIB_FORMAT_ALIAS(typename details::RemoveVolatile<typename details::RemoveReference<Argument>::ValueType>::ValueType, DRefArgument);
				// Parsing argument settings / options.
				Formatter<Char, DRefArgument>::template parse<Reader>(pReader);
				// Appending stringified value.
				Formatter<Char, DRefArgument>::template format<Writer>(pWriter, pArgument);
			}

			// Going onto the next argument
			formatHandle<Char, Reader, Writer>(pReader, pWriter, pArguments...);
		}

		template<typename Char>
		class Reader
		{
		private:
			const Char* mIterator;
			const Char* mBegin;
			const Char* mEnd;
		
		public:
			explicit Reader(const Char* pIterator, const Char* pBegin, const Char* pEnd) CXXTLIB_FORMAT_NOEXCEPT
				: mIterator(pIterator), mBegin(pBegin), mEnd(pEnd)
			{ }

			~Reader() CXXTLIB_FORMAT_NOEXCEPT
			{ }

		public:
			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR details::uint32 size() const CXXTLIB_FORMAT_NOEXCEPT
			{
				return static_cast<details::uint32>(this->mEnd - this->mIterator);
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR const Char* iterator() const CXXTLIB_FORMAT_NOEXCEPT
			{
				return this->mIterator;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR const Char* begin() const CXXTLIB_FORMAT_NOEXCEPT
			{
				return this->mBegin;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR const Char* end() const CXXTLIB_FORMAT_NOEXCEPT
			{
				return this->mEnd;
			}

		public:
			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR Reader operator +(details::int32 pOffset) CXXTLIB_FORMAT_NOEXCEPT
			{
				Reader reader = Reader(this->mIterator + pOffset, this->mBegin, this->mEnd);
				return reader;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR Reader& operator +=(details::int32 pOffset) CXXTLIB_FORMAT_NOEXCEPT
			{
				this->mIterator += pOffset;
				return *this;
			}
			
			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR Reader& operator ++() CXXTLIB_FORMAT_NOEXCEPT
			{
				this->mIterator++;
				return *this;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR Reader operator ++(details::int32) CXXTLIB_FORMAT_NOEXCEPT
			{
				Reader reader = Reader(this->mIterator, this->mBegin, this->mEnd);
				++(*this);
				return reader;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR Reader operator -(details::int32 pOffset) CXXTLIB_FORMAT_NOEXCEPT
			{
				Reader reader = Reader(this->mIterator - pOffset, this->mBegin, this->mEnd);
				return reader;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR Reader& operator -=(details::int32 pOffset) CXXTLIB_FORMAT_NOEXCEPT
			{
				this->mIterator -= pOffset;
				return *this;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR Reader& operator --() CXXTLIB_FORMAT_NOEXCEPT
			{
				this->mIterator--;
				return *this;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR Reader operator --(details::int32) CXXTLIB_FORMAT_NOEXCEPT
			{
				Reader reader = Reader(this->mIterator, this->mBegin, this->mEnd);
				--(*this);
				return reader;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR const Char& operator *() const CXXTLIB_FORMAT_NOEXCEPT
			{
				return *this->mIterator;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR bool operator ==(const Reader& pOther) const CXXTLIB_FORMAT_NOEXCEPT
			{
				return this->mIterator == pOther.iterator() && this->mBegin == pOther.begin() && this->mEnd == pOther.end();
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR bool operator !=(const Reader& pOther) const CXXTLIB_FORMAT_NOEXCEPT
			{
				return !(*this == pOther);
			}
		};

		template<typename Char>
		class HeapWriter
		{
		private:
			Char* mData;
			details::uint32 mSize;
			details::uint32 mCapacity;

		public:
			explicit HeapWriter(details::uint32 pCapacity = 4u) CXXTLIB_FORMAT_NOEXCEPT
				: mData(nullptr), mSize(0), mCapacity(pCapacity)
			{ allocate(pCapacity); }

		private:
			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR details::uint32 size() const CXXTLIB_FORMAT_NOEXCEPT
			{
				return this->mSize;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void allocate(details::uint32 pCapacity) CXXTLIB_FORMAT_NOEXCEPT
			{
				this->mCapacity = pCapacity;
				this->mData = new Char[pCapacity + 1u];
				this->mData[this->mSize] = details::move(details::FormatTraits<Char>::terminationSpecifier);
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void reallocate(details::uint32 pCapacity) CXXTLIB_FORMAT_NOEXCEPT
			{
				Char* local = new Char[pCapacity + 1u];

				if (this->mSize > pCapacity)
					this->mSize = pCapacity;
				
				for (details::uint32 i = 0; i < this->mSize; i++)
					local[i] = details::move(this->mData[i]);

				delete[] this->mData;
				this->mCapacity = pCapacity;
				this->mData = local;
			}

		public:
			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void append(Char pChar) CXXTLIB_FORMAT_NOEXCEPT
			{
				if (this->mSize + 1 > this->mCapacity)
					reallocate(this->mCapacity + this->mCapacity / 2);
				
				this->mData[this->mSize++] = pChar;
				this->mData[this->mSize] = details::FormatTraits<Char>::terminationSpecifier;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void append(const Char* const pData, details::uint32 pSize) CXXTLIB_FORMAT_NOEXCEPT
			{
				if (this->mSize + pSize > this->mCapacity)
					reallocate(pSize + this->mCapacity + this->mCapacity / 2);

				for (details::uint32 i = 0; i < pSize; i++)
					this->mData[this->mSize + i] = pData[i];

				this->mData[this->mSize += pSize] = details::FormatTraits<Char>::terminationSpecifier;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR Char* get() CXXTLIB_FORMAT_NOEXCEPT
			{
				return details::move(this->mData);
			}
		};

		template<typename Char, details::uint32 tCapacity>
		class StackWriter
		{
		private:
			Char* mData;
			details::uint32 mSize;

		public:
			explicit StackWriter(Char* pData) CXXTLIB_FORMAT_NOEXCEPT
				: mData(pData), mSize(0)
			{ }

		public:
			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR details::uint32 size() const CXXTLIB_FORMAT_NOEXCEPT
			{
				return this->mSize;
			}
			
			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void append(Char pChar) CXXTLIB_FORMAT_NOEXCEPT
			{
				if (this->mSize + 1u <= tCapacity)
					this->mData[this->mSize++] = pChar;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void append(const Char* const pData, details::uint32 pSize) CXXTLIB_FORMAT_NOEXCEPT
			{
				if (this->mSize + pSize <= tCapacity)
				{
					for (details::uint32 i = 0; i < pSize; i++)
						this->mData[this->mSize + i] = pData[i];
					
					this->mSize += pSize;
				}
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR Char* get() CXXTLIB_FORMAT_NOEXCEPT
			{
				this->mData[this->mSize] = details::FormatTraits<Char>::terminationSpecifier;
				return this->mData;
			}
		};

		/**
		 * Formats a dynamic cstring and returns a pointer to it. Note that neither this methods, nor any underlying structures and funtions deallocate
		 * this formatted cstring (the result). It is users responsibility to deallocate result cstring after they finish working with it. User can use
		 * cleanup<Char>() function to deallocate memory or store this pointer to formatted cstring inside a smart pointer.
		 */
		template<typename Char, typename... Arguments>
		static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR Char* format(const Char* const pPattern, Arguments&&... pArguments) CXXTLIB_FORMAT_NOEXCEPT
		{
			// Setting up the reader (later referenced as Context).
			details::uint32 patternLength = details::ascii::length<Char>(pPattern);
			Reader<Char> reader = Reader<Char>(pPattern, pPattern, pPattern + patternLength);
			// Setting up the writer (later referenced as Context).
			details::uint32 argumentsLength = sizeof...(pArguments);
			HeapWriter<Char> writer = HeapWriter<Char>(patternLength + argumentsLength);
			// Passing reader, writer and arguments to the handle function and returning formatted cstring
			formatHandle<Char, Reader<Char>, HeapWriter<Char>, Arguments...>(reader, writer, details::forward<Arguments>(pArguments)...);
			return writer.get();
		}

		/**
		 * Returns the length of chars written to the buffer.
		 */
		template<typename Char, details::uint32 tSize, typename... Arguments>
		static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR details::uint32 format(Char* pBuffer, const Char* const pPattern, Arguments&&... pArguments) CXXTLIB_FORMAT_NOEXCEPT
		{
			// Setting up the reader (later referenced as Context).
			Reader<Char> reader = Reader<Char>(pPattern, pPattern, pPattern + details::ascii::length<Char>(pPattern));
			// Setting up the writer with user defined initial capacity (later referenced as Context).
			StackWriter<Char, tSize> writer = StackWriter<Char, tSize>(pBuffer);
			// Passing reader, writer and arguments to the handle function and returning formatted cstring
			formatHandle<Char, Reader<Char>, StackWriter<Char, tSize>, Arguments...>(reader, writer, details::forward<Arguments>(pArguments)...);
			return writer.size();
		}

		/**
		 * Should only be used when default format function is used. Default format method creates formatted string on heap
		 * and returns it. It does not handle memory deallocation of the formatted string. That is handled by this function.
		 */
		template<typename Char>
		static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void cleanup(Char* pFormatted) CXXTLIB_FORMAT_NOEXCEPT
		{
			delete[] pFormatted;
		}

		/**
		 * Formats string and forwards it to any provided stream that supports << operator (cout, ofstream, etc). This method handles formatted cstring
		 * itself and deallocates it at the end of the function.
		 */
		template<typename Stream, typename Char, typename... Arguments>
		static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void print(Stream& pStream, const Char* const pPattern, Arguments&&... pArguments) CXXTLIB_FORMAT_NOEXCEPT
		{
			Char* formatted = format<Char, Arguments...>(pPattern, details::forward<Arguments>(pArguments)...);
			pStream << formatted;
			cleanup<Char>(formatted);
		}

		template<typename Stream, typename Char, details::uint32 tSize, typename... Arguments>
		static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void print(Stream& pStream, const Char* const pPattern, Arguments&&... pArguments) CXXTLIB_FORMAT_NOEXCEPT
		{
			Char formatted[tSize] { };
			format<Char, tSize, Arguments...>(formatted, pPattern, details::forward<Arguments>(pArguments)...);
			pStream << formatted;
		}
		
		/**
		 * Printing method for c-like streams.
		 */
		template<typename Char, typename... Arguments>
		static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void cprint(::FILE* pStream, const Char* const pPattern, Arguments&&... pArguments) CXXTLIB_FORMAT_NOEXCEPT
		{
			Char* formatted = format<Char, Arguments...>(pPattern, details::forward<Arguments>(pArguments)...);
			::fwrite(formatted, sizeof(Char), details::ascii::length<Char>(formatted), pStream);
			cleanup<Char>(formatted);
		}

		template<typename Char, details::uint32 tSize, typename... Arguments>
		static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void cprint(::FILE* pStream, const Char* const pPattern, Arguments&&... pArguments) CXXTLIB_FORMAT_NOEXCEPT
		{
			Char formatted[tSize] { };
			format<Char, tSize, Arguments...>(formatted, pPattern, details::forward<Arguments>(pArguments)...);
			::fwrite(formatted, sizeof(Char), details::ascii::length<Char>(formatted), pStream);
		}

		template<typename Char, typename Type>
		struct SpecifierOf
		{
		public:
			static CXXTLIB_FORMAT_CONSTEXPR const Char value = ' ';
		};

		#define __struct_INTERNAL_SPECIFIER_OF(DTypes, Type, Specifier) \
		template<DTypes> \
		struct SpecifierOf<Char, Type> \
		{ \
		public: \
			static CXXTLIB_FORMAT_CONSTEXPR const Char value = Specifier; \
		}

		__struct_INTERNAL_SPECIFIER_OF(typename Char, details::int8, 'd');
		__struct_INTERNAL_SPECIFIER_OF(typename Char, details::uint8, 'u');
		__struct_INTERNAL_SPECIFIER_OF(typename Char, details::int16, 'd');
		__struct_INTERNAL_SPECIFIER_OF(typename Char, details::uint16, 'u');
		__struct_INTERNAL_SPECIFIER_OF(typename Char, details::int32, 'd');
		__struct_INTERNAL_SPECIFIER_OF(typename Char, details::uint32, 'u');
		__struct_INTERNAL_SPECIFIER_OF(typename Char, float, 'f');
		__struct_INTERNAL_SPECIFIER_OF(typename Char, double, 'f');
		
		template<typename Char, details::uint32 tSize, typename Type>
		static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR const Char* precision(Char* pBuffer, Type pValue, details::uint32 pPre, details::uint32 pPost) CXXTLIB_FORMAT_NOEXCEPT
		{
			Char temp[10] { };
			temp[0] = '%';
			details::uint32 count = ::snprintf(temp + 1, 9, "%u.%u", pPre, pPost);
			temp[++count] = (Char)SpecifierOf<Char, Type>::value;

			if (count <= 0)
			{
				return nullptr;
			}

			const details::uint32 written = ::snprintf(pBuffer, tSize, temp, pValue);

			if (written > 0)
			{
				return pBuffer;
			}
			else
			{
				return nullptr;
			}
		}
	}
}

/**
 * Helper macros and cleanup.
 */

#undef struct_CUSTOM_FORMATTER

#define PARSE_IGNORE(pContext) \
for (; *pContext != cxxtlib::format::details::FormatTraits<Char>::rightCurlyBracketSpecifier; pContext++); \
pContext++;

#define CUSTOM_TYPE_OF(Type) \
struct cxxtlib::format::TypeOf<Type> \
{ \
public: \
	static CXXTLIB_FORMAT_CONSTEXPR const cxxtlib::format::FormatArgumentType value = cxxtlib::format::FormatArgumentType::Custom; \
};

#define CUSTOM_FORMATTER(Type) \
struct cxxtlib::format::Formatter<Type> : public cxxtlib::format::FormatterBase<Char>

/**
 * Custom formatter for std::basic_string<Char, Traits>
 */

#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_BASIC_STRING_FORMATTER == 1

#include <string>

template<typename Char, typename Traits>
CUSTOM_TYPE_OF(::std::basic_string<Char COMMA Traits>);

template<typename Char, typename Traits>
CUSTOM_FORMATTER(Char COMMA ::std::basic_string<Char COMMA Traits>)
{
public:
	template<typename Context>
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	}

	template<typename Context>
	static void format(Context& pContext, const ::std::basic_string<Char, Traits>& pValue)
	{
		pContext.append(pValue.data(), (details::uint32)pValue.size()); 
	}
};

#endif

/**
 * Custom formatter for std::array<Type, size>
 */

#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_ARRAY_FORMATTER == 1

#include <array>

template<typename Type, ::std::size_t tSize>
CUSTOM_TYPE_OF(::std::array<Type COMMA tSize>);

template<typename Char, typename Type, ::std::size_t tSize>
CUSTOM_FORMATTER(Char COMMA ::std::array<Type COMMA tSize>)
{
public:
	template<typename Context>
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	}

	template<typename Context>
	static void format(Context& pContext, const ::std::array<Type, tSize>& pValue)
	{
		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::leftSquareBracketSpecifier);
		Formatter<Char, Type>::format(pContext, *pValue.begin());

		CXXTLIB_FORMAT_ALIAS(typename ::std::array<Type COMMA tSize>::const_iterator, ConstIterator);
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::spaceSpecifier);
			Formatter<Char, Type>::format(pContext, *iterator);
		}

		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::rightSquareBracketSpecifier);
	}
};

#endif

/**
 * Custom formatter for std::vector<Type>
 */

#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_VECTOR_FORMATTER == 1

#include <vector>

template<typename Type>
CUSTOM_TYPE_OF(::std::vector<Type>);

template<typename Char, typename Type>
CUSTOM_FORMATTER(Char COMMA ::std::vector<Type>)
{
public:
	template<typename Context>
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	}

	template<typename Context>
	static void format(Context& pContext, const ::std::vector<Type>& pValue)
	{
		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::leftSquareBracketSpecifier);
		Formatter<Char, Type>::format(pContext, *pValue.begin());

		CXXTLIB_FORMAT_ALIAS(typename ::std::vector<Type>::const_iterator, ConstIterator);
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::spaceSpecifier);
			Formatter<Char, Type>::format(pContext, *iterator);
		}
	
		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::rightSquareBracketSpecifier);
	}
};

#endif

/**
 * Custom formatter for std::list<Type>
 */

#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_LIST_FORMATTER == 1

#include <list>

template<typename Type>
CUSTOM_TYPE_OF(::std::list<Type>);

template<typename Char, typename Type>
CUSTOM_FORMATTER(Char COMMA ::std::list<Type>)
{
public:
	template<typename Context>
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	}

	template<typename Context>
	static void format(Context& pContext, const ::std::list<Type>& pValue)
	{
		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::leftSquareBracketSpecifier);
		Formatter<Char, Type>::format(pContext, *pValue.begin());

		CXXTLIB_FORMAT_ALIAS(typename ::std::list<Type>::const_iterator, ConstIterator);
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::spaceSpecifier);
			Formatter<Char, Type>::format(pContext, *iterator);
		}
	
		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::rightSquareBracketSpecifier);
	}
};

#endif

/**
 * Custom formatter for std::deque<Type>
 */

#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_DEQUE_FORMATTER == 1

#include <deque>

template<typename Type>
CUSTOM_TYPE_OF(::std::deque<Type>);

template<typename Char, typename Type>
CUSTOM_FORMATTER(Char COMMA ::std::deque<Type>)
{
public:
	template<typename Context>
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	}

	template<typename Context>
	static void format(Context& pContext, const ::std::deque<Type>& pValue)
	{
		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::leftSquareBracketSpecifier);
		Formatter<Char, Type>::format(pContext, *pValue.begin());

		CXXTLIB_FORMAT_ALIAS(typename ::std::deque<Type>::const_iterator, ConstIterator);
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::spaceSpecifier);
			Formatter<Char, Type>::format(pContext, *iterator);
		}
	
		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::rightSquareBracketSpecifier);
	}
};

#endif

/**
 * Custom formatter for std::forward_list<Type>
 */

#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_FORWARD_LIST_FORMATTER == 1

#include <forward_list>

template<typename Type>
CUSTOM_TYPE_OF(::std::forward_list<Type>);

template<typename Char, typename Type>
CUSTOM_FORMATTER(Char COMMA ::std::forward_list<Type>)
{
public:
	template<typename Context>
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	}

	template<typename Context>
	static void format(Context& pContext, const ::std::forward_list<Type>& pValue)
	{
		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::leftSquareBracketSpecifier);
		Formatter<Char, Type>::format(pContext, *pValue.begin());

		CXXTLIB_FORMAT_ALIAS(typename ::std::forward_list<Type>::const_iterator, ConstIterator);
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::spaceSpecifier);
			Formatter<Char, Type>::format(pContext, *iterator);
		}

		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::rightSquareBracketSpecifier);
	}
};

#endif

/**
 * Custom formatter for std::initializer_list<Type>
 */

#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_INITIALIZER_LIST_FORMATTER == 1

#include <initializer_list>

template<typename Type>
CUSTOM_TYPE_OF(::std::initializer_list<Type>);

template<typename Char, typename Type>
CUSTOM_FORMATTER(Char COMMA ::std::initializer_list<Type>)
{
public:
	template<typename Context>
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	}

	template<typename Context>
	static void format(Context& pContext, const ::std::initializer_list<Type>& pValue)
	{
		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::leftSquareBracketSpecifier);
		Formatter<Char, Type>::format(pContext, *pValue.begin());

		CXXTLIB_FORMAT_ALIAS(typename ::std::initializer_list<Type>::const_iterator, ConstIterator);
		for (ConstIterator iterator = pValue.begin() + 1; iterator != pValue.end(); iterator++)
		{
			Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::spaceSpecifier);
			Formatter<Char, Type>::format(pContext, *iterator);
		}

		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::rightSquareBracketSpecifier);
	}
};

#endif

/**
 * Custom formatter for std::pair<Key, Value>
 */

#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_PAIR_FORMATTER == 1

#include <utility> // For std::pair<Key, Value>

template<typename Key, typename Value>
CUSTOM_TYPE_OF(::std::pair<Key COMMA Value>);

template<typename Char, typename Key, typename Value>
CUSTOM_FORMATTER(Char COMMA ::std::pair<Key COMMA Value>)
{
public:
	template<typename Context>
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	}

	template<typename Context>
	static void format(Context& pContext, const ::std::pair<Key, Value>& pValue)
	{
		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::leftSquareBracketSpecifier);
		Formatter<Char, Key>::format(pContext, pValue.first);
		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::spaceSpecifier);
		Formatter<Char, Value>::format(pContext, pValue.second);
		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::rightSquareBracketSpecifier);
	}
};

#endif

/**
 * Custom formatter for std::set<Type>
 */

#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_SET_FORMATTER == 1

#include <set>

template<typename Type>
CUSTOM_TYPE_OF(::std::set<Type>);

template<typename Char, typename Type>
CUSTOM_FORMATTER(Char COMMA ::std::set<Type>)
{
public:
	template<typename Context>
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	}

	template<typename Context>
	static void format(Context& pContext, const ::std::set<Type>& pValue)
	{
		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::leftSquareBracketSpecifier);
		Formatter<Char, Type>::format(pContext, *pValue.begin());

		CXXTLIB_FORMAT_ALIAS(typename ::std::set<Type>::const_iterator, ConstIterator);
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::spaceSpecifier);
			Formatter<Char, Type>::format(pContext, *iterator);
		}

		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::rightSquareBracketSpecifier);
	}
};

#endif

/**
 * Custom formatter for std::unordered_set<Type>
 */

#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_UNORDERED_SET_FORMATTER == 1

#include <unordered_set>

template<typename Type>
CUSTOM_TYPE_OF(::std::unordered_set<Type>);

template<typename Char, typename Type>
CUSTOM_FORMATTER(Char COMMA ::std::unordered_set<Type>)
{
public:
	template<typename Context>
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	}

	template<typename Context>
	static void format(Context& pContext, const ::std::unordered_set<Type>& pValue)
	{
		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::leftSquareBracketSpecifier);
		Formatter<Char, Type>::format(pContext, *pValue.begin());

		CXXTLIB_FORMAT_ALIAS(typename ::std::unordered_set<Type>::const_iterator, ConstIterator);
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::spaceSpecifier);
			Formatter<Char, Type>::format(pContext, *iterator);
		}

		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::rightSquareBracketSpecifier);
	}
};

#endif

/**
 * Custom formatter for std::map<Key, Value>
 */

#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_MAP_FORMATTER == 1

#include <map>

template<typename Key, typename Value>
CUSTOM_TYPE_OF(::std::map<Key COMMA Value>);

template<typename Char, typename Key, typename Value>
CUSTOM_FORMATTER(Char COMMA ::std::map<Key COMMA Value>)
{
public:
	template<typename Context>
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	}

	template<typename Context>
	static void format(Context& pContext, const ::std::map<Key, Value>& pValue)
	{
		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::leftSquareBracketSpecifier);
		Formatter<Char, ::std::pair<Key, Value>>::format(pContext, *pValue.begin());

		CXXTLIB_FORMAT_ALIAS(typename ::std::map<Key COMMA Value>::const_iterator, ConstIterator);
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::spaceSpecifier);
			Formatter<Char, ::std::pair<Key, Value>>::format(pContext, *iterator);
		}

		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::rightSquareBracketSpecifier);
	}
};

#endif

/**
 * Custom formatter for std::unordered_map<Key, Value>
 */

#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_UNORDERED_MAP_FORMATTER == 1

#include <unordered_map>

template<typename Key, typename Value>
CUSTOM_TYPE_OF(::std::unordered_map<Key COMMA Value>);

template<typename Char, typename Key, typename Value>
CUSTOM_FORMATTER(Char COMMA ::std::unordered_map<Key COMMA Value>)
{
public:
	template<typename Context>
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	}

	template<typename Context>
	static void format(Context& pContext, const ::std::unordered_map<Key, Value>& pValue)
	{
		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::leftSquareBracketSpecifier);
		Formatter<Char, ::std::pair<Key, Value>>::format(pContext, *pValue.begin());

		CXXTLIB_FORMAT_ALIAS(typename ::std::unordered_map<Key COMMA Value>::const_iterator, ConstIterator);
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::spaceSpecifier);
			Formatter<Char, ::std::pair<Key, Value>>::format(pContext, *iterator);
		}

		Formatter<Char, Char>::format(pContext, details::FormatTraits<Char>::rightSquareBracketSpecifier);
	}
};

#endif

#endif
