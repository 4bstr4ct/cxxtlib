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

#define NONE

namespace cxxtlib
{
	namespace format
	{
		namespace details
		{
			/**
			 * A type represeting null.
			 */
			using null = decltype(nullptr);

			/**
			 * A type representing signed char.
			 */
			using int8 = signed char;

			/**
			 * A type representing unsigned char.
			 */
			using uint8 = unsigned char;
			
			/**
			 * A type representing signed short.
			 */
			using int16 = signed short;

			/**
			 * A type representing unsigned short.
			 */
			using uint16 = unsigned short;

			/**
			 * A type representing signed int.
			 */
			using int32 = signed int;
			
			/**
			 * A type representing unsigned int.
			 */
			using uint32 = unsigned int;

			/**
			 * A type representing signed long long.
			 */
			using int64 = signed long long;
			
			/**
			 * A type representing unsigned long long.
			 */
			using uint64 = unsigned long long;

			/**
			 * A type representing long double.
			 */
			using ldouble = long double;

			struct FormatTraits
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

			namespace ascii
			{
				static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR uint32 length(const char* pString) CXXTLIB_FORMAT_NOEXCEPT
				{
					uint32 count = 0;
					while (pString[count]) count++;
					return count;
				}

				static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR char* fill(char* pString, char pValue, uint32 pCount) CXXTLIB_FORMAT_NOEXCEPT
				{
					char* head = pString;
					for (uint32 index = 0; index < pCount; index++) head[index] = pValue;
					return pString;
				}

				static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR char* copy(char* destination, const char* source) CXXTLIB_FORMAT_NOEXCEPT
				{
					char* head = destination;
					while((*destination++ = *source++) != '\0');
					return head;
				}

				static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR char* copy(char* destination, const char* source, uint32 pCount) CXXTLIB_FORMAT_NOEXCEPT
				{
					char* head = destination;
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
			}

			// Add constant
			template<typename Type>
			struct AddConst
			{
			public:
				using ValueType = const Type;
			};

			// Remove constant
			template<typename Type>
			struct RemoveConst
			{
			public:
				using ValueType = Type;
			};
			
			template<typename Type>
			struct RemoveConst<const Type>
			{
			public:
				using ValueType = Type;
			};

			// Add volatile
			template<typename Type>
			struct AddVolatile
			{
			public:
				using ValueType = volatile Type;
			};
			
			// Remove volatile
			template<typename Type>
			struct RemoveVolatile
			{
			public:
				using ValueType = Type;
			};

			template<typename Type>
			struct RemoveVolatile<volatile Type>
			{
			public:
				using ValueType = Type;
			};

			// Add constant volatile
			template<typename Type>
			struct AddConstVolatile
			{
			public:
				using ValueType = typename AddConst<typename AddVolatile<Type>::ValueType>::ValueType;
			};

			// Remove constant volatile
			template<typename Type>
			struct RemoveConstVolatile
			{
			public:
				using ValueType = typename RemoveConst<typename RemoveVolatile<Type>::ValueType>::ValueType;
			};

			// Remove reference
			template<typename Type>
			struct RemoveReference
			{
			public:
				using ValueType = Type;
			};
			
			template<typename Type>
			struct RemoveReference<Type&>
			{
			public:
				using ValueType = Type;
			};

			template<typename Type>
			struct RemoveReference<Type&&>
			{
			public:
				using ValueType = Type;
			};

			// Integral constant
			template<typename Type, Type tValue>
			struct IntegralConstant
			{
			public:
				using ValueType = Type;

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
			using BoolConstant = IntegralConstant<bool, tValue>;
#endif

			using TrueType = IntegralConstant<bool, true>;

			using FalseType = IntegralConstant<bool, false>;

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
				using ValueType = IfTrue;
			};

			template<typename IfTrue, typename IfFalse>
			struct Conditional<false, IfTrue, IfFalse>
			{
			public:
				using ValueType = IfFalse;
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
				using ValueType = Type;
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
				using ValueType = Type;
			};

			template<typename Type>
			struct AddLValueReferenceHelper<Type, true>
			{
			public:
				using ValueType = Type&;
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
				using ValueType = Type;
			};

			template<typename Type>
			struct AddRValueReferenceHelper<Type, true>
			{
			public:
				using ValueType = Type&&;
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
				using ValueType = Type;
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
		struct FormatOf
		{
		public:
			static CXXTLIB_FORMAT_CONSTEXPR const FormatArgumentType value = FormatArgumentType::None;
		};

		#define __struct_INTERNAL_FORMAT_OF(Dependencies, Type, FType) \
		template<Dependencies> \
		struct FormatOf<Type> \
		{ \
		public: \
			static CXXTLIB_FORMAT_CONSTEXPR const FormatArgumentType value = FType; \
		}

		__struct_INTERNAL_FORMAT_OF(NONE, bool, FormatArgumentType::Bool);
		__struct_INTERNAL_FORMAT_OF(NONE, char, FormatArgumentType::Char);
		__struct_INTERNAL_FORMAT_OF(NONE, details::int8, FormatArgumentType::Int8);
		__struct_INTERNAL_FORMAT_OF(NONE, details::uint8, FormatArgumentType::UInt8);
		__struct_INTERNAL_FORMAT_OF(NONE, details::int16, FormatArgumentType::Int16);
		__struct_INTERNAL_FORMAT_OF(NONE, details::uint16, FormatArgumentType::UInt16);
		__struct_INTERNAL_FORMAT_OF(NONE, details::int32, FormatArgumentType::Int32);
		__struct_INTERNAL_FORMAT_OF(NONE, details::uint32, FormatArgumentType::UInt32);
		__struct_INTERNAL_FORMAT_OF(NONE, details::int64, FormatArgumentType::Int64);
		__struct_INTERNAL_FORMAT_OF(NONE, details::uint64, FormatArgumentType::UInt64);
		__struct_INTERNAL_FORMAT_OF(NONE, float, FormatArgumentType::Float);
		__struct_INTERNAL_FORMAT_OF(NONE, double, FormatArgumentType::Double);
		__struct_INTERNAL_FORMAT_OF(NONE, details::ldouble, FormatArgumentType::LDouble);
		__struct_INTERNAL_FORMAT_OF(typename Type, Type*, FormatArgumentType::Pointer);
		__struct_INTERNAL_FORMAT_OF(typename Type, const Type*, FormatArgumentType::Pointer);
		__struct_INTERNAL_FORMAT_OF(NONE, details::null, FormatArgumentType::Pointer);
		__struct_INTERNAL_FORMAT_OF(NONE, const char*, FormatArgumentType::CString);
		__struct_INTERNAL_FORMAT_OF(NONE, const char[], FormatArgumentType::CString);
		__struct_INTERNAL_FORMAT_OF(typename details::uint32 tSize, const char[tSize], FormatArgumentType::CString);
		
		struct FormatterHelpers
		{
		public:
			template<typename Context>
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parseIgnore(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				for (; *pContext != details::FormatTraits::rightCurlyBracketSpecifier; pContext++);
				pContext++;
			}
		};

		struct FormatterBase
		{ };

		template<typename Type, typename Enable = void>
		struct Formatter
		{
			static_assert(FormatOf<Type>::value != FormatArgumentType::None, "Provided type does not have a formatter!");
		};

		template<typename Type>
		using FormatterEnabler = typename details::EnableIf
		<
			details::BoolConstant
			<
				details::IntegralConstant
				<
					FormatArgumentType,
					FormatOf<Type>::value
				>::value != FormatArgumentType::None
			>::value
		>::ValueType;

		#define __struct_INTERNAL_FORMATTER(Dependencies, Type, PFunc, FFunc) \
		template<Dependencies> \
		struct Formatter<Type, FormatterEnabler<Type>> : public FormatterBase \
		{ \
		public: \
			template<typename Context> \
			PFunc \
			 \
			template<typename Context> \
			FFunc \
		}

		__struct_INTERNAL_FORMATTER(NONE, bool,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext COMMA bool pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				pContext.append(
					pValue ? details::FormatTraits::trueStringified
						: details::FormatTraits::falseStringified COMMA
					pValue ? 4u : 5u);
			}
		);

		__struct_INTERNAL_FORMATTER(NONE, char,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext COMMA char pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				pContext.append(pValue);
			}
		);

		__struct_INTERNAL_FORMATTER(NONE, details::int8,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext COMMA details::int8 pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 5u;
				char buffer[size] { };
				const details::int32 written = ::snprintf(buffer COMMA size COMMA "%d" COMMA pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer COMMA written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(NONE, details::uint8,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext COMMA details::uint8 pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 5u;
				char buffer[size] { };
				const details::int32 written = ::snprintf(buffer COMMA size COMMA "%u" COMMA pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer COMMA written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(NONE, details::int16,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext COMMA details::int16 pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 7u;
				char buffer[size] { };
				const details::int32 written = ::snprintf(buffer COMMA size COMMA "%d" COMMA pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer COMMA written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(NONE, details::uint16,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext COMMA details::uint16 pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 7u;
				char buffer[size] { };
				const details::int32 written = ::snprintf(buffer COMMA size COMMA "%u" COMMA pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer COMMA written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(NONE, details::int32,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext COMMA details::int32 pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 12u;
				char buffer[size] { };
				const details::int32 written = ::snprintf(buffer COMMA size COMMA "%d" COMMA pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer COMMA written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(NONE, details::uint32,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext COMMA details::uint32 pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 12u;
				char buffer[size] { };
				const details::int32 written = ::snprintf(buffer COMMA size COMMA "%u" COMMA pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer COMMA written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(NONE, details::int64,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext COMMA details::int64 pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 21u;
				char buffer[size] { };
				const details::int32 written = ::snprintf(buffer COMMA size COMMA "%lld" COMMA pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer COMMA written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(NONE, details::uint64,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext COMMA details::uint64 pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 21u;
				char buffer[size] { };
				const details::int32 written = ::snprintf(buffer COMMA size COMMA "%llu" COMMA pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer COMMA written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(NONE, float,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext COMMA float pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 25u;
				char buffer[size] { };
				const details::int32 written = ::snprintf(buffer COMMA size COMMA "%f" COMMA pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer COMMA written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(NONE, double,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext COMMA double pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 25u;
				char buffer[size] { };
				const details::int32 written = ::snprintf(buffer COMMA size COMMA "%f" COMMA pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer COMMA written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(NONE, details::ldouble,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext COMMA details::ldouble pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 26u;
				char buffer[size] { };
				const details::int32 written = ::snprintf(buffer COMMA size COMMA "%Lf" COMMA pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer COMMA written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(typename Type, Type*,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext COMMA Type* pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 19u;
				char buffer[size] { };
				const details::int32 written = ::snprintf(buffer COMMA size COMMA "0x%p" COMMA (void*)pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer COMMA written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(typename Type, const Type*,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext COMMA const Type* pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				const details::uint32 size = 19u;
				char buffer[size] { };
				const details::int32 written = ::snprintf(buffer COMMA size COMMA "0x%p" COMMA (const void*)pValue);
				
				if (written >= 0)
				{
					pContext.append(buffer COMMA written);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(NONE, details::null,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext COMMA details::null pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				pContext.append(details::FormatTraits::nullptrStringified COMMA 7u);
			}
		);

		__struct_INTERNAL_FORMATTER(NONE, const char*,
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext COMMA const char* pValue) CXXTLIB_FORMAT_NOEXCEPT
			{
				if (pValue)
				{
					pContext.append(pValue COMMA details::ascii::length(pValue));
				}
				else
				{
					pContext.append(details::FormatTraits::nullptrStringified COMMA 7u);
				}
			}
		);

		__struct_INTERNAL_FORMATTER(NONE, const char[],
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext COMMA const char pValue[]) CXXTLIB_FORMAT_NOEXCEPT
			{
				pContext.append(pValue COMMA details::ascii::length(pValue));
			}
		);

		__struct_INTERNAL_FORMATTER(typename details::uint32 tSize, const char[tSize],
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void parse(Context& pContext) CXXTLIB_FORMAT_NOEXCEPT
			{
				FormatterHelpers::template parseIgnore<Context>(pContext);
			},
			static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void format(Context& pContext COMMA const char pValue[tSize]) CXXTLIB_FORMAT_NOEXCEPT
			{
				pContext.append(pValue COMMA tSize - 1);
			}
		);

		template<typename Reader, typename Writer>
		static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void formatHandle(Reader& pReader, Writer& pWriter) CXXTLIB_FORMAT_NOEXCEPT
		{
			pWriter.append(pReader.iterator(), pReader.size());
		}

		template<typename Reader, typename Writer, typename Argument, typename... Arguments>
		static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void formatHandle(Reader& pReader, Writer& pWriter, Argument&& pArgument, Arguments&&... pArguments) CXXTLIB_FORMAT_NOEXCEPT
		{
			// Setting pointer to the beggining for this section of pattern
			const char* previous = pReader.iterator();
			// Iterating untill next '{' character in pattern is present
			for (; *pReader != details::FormatTraits::leftCurlyBracketSpecifier && pReader.iterator() != pReader.end(); pReader++);

			if (*pReader == details::FormatTraits::leftCurlyBracketSpecifier)
			{
				// Appending text from pattern.
				pWriter.append(previous, (details::uint32)(pReader.iterator() - previous));
				// Removing references for types and volatiles.
				using DRefArgument = typename details::RemoveVolatile<typename details::RemoveReference<Argument>::ValueType>::ValueType;
				// Parsing argument settings / options.
				Formatter<DRefArgument>::template parse<Reader>(pReader);
				// Appending stringified value.
				Formatter<DRefArgument>::template format<Writer>(pWriter, pArgument);
			}

			// Going onto the next argument
			formatHandle<Reader, Writer>(pReader, pWriter, pArguments...);
		}

		class Reader
		{
		private:
			const char* mIterator;
			const char* mBegin;
			const char* mEnd;
		
		public:
			explicit Reader(const char* pIterator, const char* pBegin, const char* pEnd) CXXTLIB_FORMAT_NOEXCEPT
				: mIterator(pIterator), mBegin(pBegin), mEnd(pEnd)
			{ }

			~Reader() CXXTLIB_FORMAT_NOEXCEPT
			{ }

		public:
			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR details::uint32 size() const CXXTLIB_FORMAT_NOEXCEPT
			{
				return static_cast<details::uint32>(this->mEnd - this->mIterator);
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR const char* iterator() const CXXTLIB_FORMAT_NOEXCEPT
			{
				return this->mIterator;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR const char* begin() const CXXTLIB_FORMAT_NOEXCEPT
			{
				return this->mBegin;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR const char* end() const CXXTLIB_FORMAT_NOEXCEPT
			{
				return this->mEnd;
			}

		public:
			CXXTLIB_FORMAT_INLINE Reader operator +(details::int32 pOffset) CXXTLIB_FORMAT_NOEXCEPT
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

			CXXTLIB_FORMAT_INLINE Reader operator ++(details::int32) CXXTLIB_FORMAT_NOEXCEPT
			{
				Reader reader = Reader(this->mIterator, this->mBegin, this->mEnd);
				++(*this);
				return reader;
			}

			CXXTLIB_FORMAT_INLINE Reader operator -(details::int32 pOffset) CXXTLIB_FORMAT_NOEXCEPT
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

			CXXTLIB_FORMAT_INLINE Reader operator --(details::int32) CXXTLIB_FORMAT_NOEXCEPT
			{
				Reader reader = Reader(this->mIterator, this->mBegin, this->mEnd);
				--(*this);
				return reader;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR const char& operator *() const CXXTLIB_FORMAT_NOEXCEPT
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

		class HeapWriter
		{
		private:
			char* mData;
			details::uint32 mSize;
			details::uint32 mCapacity;

		public:
			explicit HeapWriter(details::uint32 pCapacity = 4u) CXXTLIB_FORMAT_NOEXCEPT
				: mData(nullptr), mSize(0), mCapacity(pCapacity)
			{ allocate(pCapacity); }

			~HeapWriter() CXXTLIB_FORMAT_NOEXCEPT
			{ }

		private:
			CXXTLIB_FORMAT_INLINE void allocate(details::uint32 pCapacity) CXXTLIB_FORMAT_NOEXCEPT
			{
				this->mCapacity = pCapacity;
				this->mData = new char[pCapacity + 1u];
				this->mData[this->mSize] = details::move(details::FormatTraits::terminationSpecifier);
			}

			CXXTLIB_FORMAT_INLINE void reallocate(details::uint32 pCapacity) CXXTLIB_FORMAT_NOEXCEPT
			{
				char* local = new char[pCapacity + 1u];

				if (this->mSize > pCapacity)
					this->mSize = pCapacity;
				
				for (details::uint32 i = 0; i < this->mSize; i++)
					local[i] = details::move(this->mData[i]);

				delete[] this->mData;
				this->mCapacity = pCapacity;
				this->mData = local;
			}

		public:
			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR details::uint32 size() const CXXTLIB_FORMAT_NOEXCEPT
			{
				return this->mSize;
			}

			CXXTLIB_FORMAT_INLINE void CXXTLIB_FORMAT_CONSTEXPR append(char pChar) CXXTLIB_FORMAT_NOEXCEPT
			{
				if (this->mSize + 1 > this->mCapacity)
					reallocate(this->mCapacity + this->mCapacity / 2);
				
				this->mData[this->mSize++] = pChar;
				this->mData[this->mSize] = details::FormatTraits::terminationSpecifier;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void append(const char* const pData, details::uint32 pSize) CXXTLIB_FORMAT_NOEXCEPT
			{
				if (this->mSize + pSize > this->mCapacity)
					reallocate(pSize + this->mCapacity + this->mCapacity / 2);

				for (details::uint32 i = 0; i < pSize; i++)
					this->mData[this->mSize + i] = pData[i];

				this->mData[this->mSize += pSize] = details::FormatTraits::terminationSpecifier;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR char* get() CXXTLIB_FORMAT_NOEXCEPT
			{
				return this->mData;
			}
		};

		template<details::uint32 tCapacity>
		class StackWriter
		{
		private:
			char* mData;
			details::uint32 mSize;

		public:
			explicit StackWriter(char* pData) CXXTLIB_FORMAT_NOEXCEPT
				: mData(pData), mSize(0)
			{ }

			~StackWriter() CXXTLIB_FORMAT_NOEXCEPT
			{ }

		public:
			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR details::uint32 size() const CXXTLIB_FORMAT_NOEXCEPT
			{
				return this->mSize;
			}
			
			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void append(char pChar) CXXTLIB_FORMAT_NOEXCEPT
			{
				if (this->mSize + 1u <= tCapacity)
					this->mData[this->mSize++] = pChar;
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void append(const char* const pData, details::uint32 pSize) CXXTLIB_FORMAT_NOEXCEPT
			{
				if (this->mSize + pSize <= tCapacity)
				{
					for (details::uint32 i = 0; i < pSize; i++)
						this->mData[this->mSize + i] = pData[i];
					
					this->mSize += pSize;
				}
			}

			CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR char* get() CXXTLIB_FORMAT_NOEXCEPT
			{
				this->mData[this->mSize] = details::FormatTraits::terminationSpecifier;
				return this->mData;
			}
		};

		/**
		 * Formats a dynamic cstring and returns a pointer to it. Note that neither this methods, nor any underlying structures and funtions deallocate
		 * this formatted cstring (the result). It is users responsibility to deallocate result cstring after they finish working with it. User can use
		 * cleanup() function to deallocate memory or store this pointer to formatted cstring inside a smart pointer.
		 */
		template<typename... Arguments>
		static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR char* format(const char* const pPattern, Arguments&&... pArguments) CXXTLIB_FORMAT_NOEXCEPT
		{
			// Setting up the reader (later referenced as Context).
			details::uint32 patternLength = details::ascii::length(pPattern);
			Reader reader = Reader(pPattern, pPattern, pPattern + patternLength);
			// Setting up the writer (later referenced as Context).
			HeapWriter writer = HeapWriter(patternLength + sizeof...(pArguments) * 2);
			// Passing reader, writer and arguments to the handle function and returning formatted cstring
			formatHandle<Reader, HeapWriter, Arguments...>(reader, writer, details::forward<Arguments>(pArguments)...);
			return writer.get();
		}

		/**
		 * Returns the length of chars written to the buffer.
		 */
		template<details::uint32 tSize, typename... Arguments>
		static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR details::uint32 format(char* pBuffer, const char* const pPattern, Arguments&&... pArguments) CXXTLIB_FORMAT_NOEXCEPT
		{
			// Setting up the reader (later referenced as Context).
			Reader reader = Reader(pPattern, pPattern, pPattern + details::ascii::length(pPattern));
			// Setting up the writer with user defined initial capacity (later referenced as Context).
			StackWriter<tSize> writer = StackWriter<tSize>(pBuffer);
			// Passing reader, writer and arguments to the handle function and returning formatted cstring
			formatHandle<Reader, StackWriter<tSize>, Arguments...>(reader, writer, details::forward<Arguments>(pArguments)...);
			return writer.size();
		}

		/**
		 * Should only be used when default format function is used. Default format method creates formatted string on heap
		 * and returns it. It does not handle memory deallocation of the formatted string. That is handled by this function.
		 */
		static CXXTLIB_FORMAT_INLINE void cleanup(char* pFormatted) CXXTLIB_FORMAT_NOEXCEPT
		{
			delete[] pFormatted;
		}

		template<details::uint32 tSize>
		static CXXTLIB_FORMAT_INLINE void cleanup(char* pFormatted) CXXTLIB_FORMAT_NOEXCEPT
		{
			details::ascii::fill(pFormatted, char(), tSize);
		}

		/**
		 * Formats string and forwards it to any provided stream that supports << operator (cout, ofstream, etc). This method handles formatted cstring
		 * itself and deallocates it at the end of the function.
		 */
		template<typename Stream, typename... Arguments>
		static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void print(Stream& pStream, const char* const pPattern, Arguments&&... pArguments) CXXTLIB_FORMAT_NOEXCEPT
		{
			char* formatted = format<Arguments...>(pPattern, details::forward<Arguments>(pArguments)...);
			pStream << formatted;
			cleanup(formatted);
		}

		template<typename Stream, details::uint32 tSize, typename... Arguments>
		static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void print(Stream& pStream, const char* const pPattern, Arguments&&... pArguments) CXXTLIB_FORMAT_NOEXCEPT
		{
			char formatted[tSize] { };
			format<tSize, Arguments...>(formatted, pPattern, details::forward<Arguments>(pArguments)...);
			pStream << formatted;
		}
		
		/**
		 * Printing method for c-like streams.
		 */
		template<typename... Arguments>
		static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void cprint(::FILE* pStream, const char* const pPattern, Arguments&&... pArguments) CXXTLIB_FORMAT_NOEXCEPT
		{
			char* formatted = format<Arguments...>(pPattern, details::forward<Arguments>(pArguments)...);
			::fwrite(formatted, sizeof(char), details::ascii::length(formatted), pStream);
			cleanup(formatted);
		}

		template<details::uint32 tSize, typename... Arguments>
		static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR void cprint(::FILE* pStream, const char* const pPattern, Arguments&&... pArguments) CXXTLIB_FORMAT_NOEXCEPT
		{
			char formatted[tSize] { };
			format<tSize, Arguments...>(formatted, pPattern, details::forward<Arguments>(pArguments)...);
			::fwrite(formatted, sizeof(char), details::ascii::length(formatted), pStream);
		}

		template<typename Type>
		struct SpecifierOf
		{
		public:
			static CXXTLIB_FORMAT_CONSTEXPR const char value = ' ';
		};

		#define __struct_INTERNAL_SPECIFIER_OF(Dependencies, Type, Specifier) \
		template<Dependencies> \
		struct SpecifierOf<Type> \
		{ \
		public: \
			static CXXTLIB_FORMAT_CONSTEXPR const char value = Specifier; \
		}

		__struct_INTERNAL_SPECIFIER_OF(NONE, details::int8, 'd');
		__struct_INTERNAL_SPECIFIER_OF(NONE, details::uint8, 'u');
		__struct_INTERNAL_SPECIFIER_OF(NONE, details::int16, 'd');
		__struct_INTERNAL_SPECIFIER_OF(NONE, details::uint16, 'u');
		__struct_INTERNAL_SPECIFIER_OF(NONE, details::int32, 'd');
		__struct_INTERNAL_SPECIFIER_OF(NONE, details::uint32, 'u');
		__struct_INTERNAL_SPECIFIER_OF(NONE, float, 'f');
		__struct_INTERNAL_SPECIFIER_OF(NONE, double, 'f');
		
		template<details::uint32 tSize, typename Type>
		static CXXTLIB_FORMAT_INLINE CXXTLIB_FORMAT_CONSTEXPR const char* precision(char* pBuffer, Type pValue, details::uint32 pPre, details::uint32 pPost) CXXTLIB_FORMAT_NOEXCEPT
		{
			char temp[10] { };
			temp[0] = '%';
			details::uint32 count = ::snprintf(temp + 1, 9, "%u.%u", pPre, pPost);
			temp[++count] = SpecifierOf<Type>::value;

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

#undef __struct_INTERNAL_FORMAT_OF
#undef __struct_INTERNAL_FORMATTER
#undef __struct_INTERNAL_SPECIFIER_OF

#define PARSE_IGNORE(pContext) \
for (; *pContext != details::FormatTraits::rightCurlyBracketSpecifier; pContext++); \
pContext++;

#define struct_CUSTOM_FORMAT_OF(Dependencies, Type) \
namespace cxxtlib \
{ \
	namespace format \
	{ \
		template<Dependencies> \
		struct FormatOf<Type> \
		{ \
		public: \
			static CXXTLIB_FORMAT_CONSTEXPR const FormatArgumentType value = FormatArgumentType::Custom; \
		}; \
	} \
}

#define struct_CUSTOM_FORMATTER(Dependencies, Type, PFunc, FFunc) \
namespace cxxtlib \
{ \
	namespace format \
	{ \
		template<Dependencies> \
		struct Formatter<Type, FormatterEnabler<Type>> : public FormatterBase \
		{ \
		public: \
			template<typename Context> \
			PFunc \
				\
			template<typename Context> \
			FFunc \
		}; \
	} \
}

#endif

/**
 * Standard string formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_STRING_FORMATTER == 1

#ifndef STD_STRING_FORMATTER
#define STD_STRING_FORMATTER

#include <string>

struct_CUSTOM_FORMAT_OF(typename Char COMMA typename Traits COMMA typename Allocator, ::std::basic_string<Char COMMA Traits COMMA Allocator>);
struct_CUSTOM_FORMATTER(typename Char COMMA typename Traits COMMA typename Allocator, ::std::basic_string<Char COMMA Traits COMMA Allocator>,
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	},
	static void format(Context& pContext COMMA const ::std::basic_string<Char COMMA Traits COMMA Allocator>& pValue)
	{
		pContext.append(pValue.data() COMMA pValue.size());
	}
);

#endif

#endif

/**
 * Standard initializer list formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_INITIALIZER_LIST_FORMATTER == 1

#ifndef STD_INITIALIZER_LIST_FORMATTER
#define STD_INITIALIZER_LIST_FORMATTER

#include <initializer_list>

struct_CUSTOM_FORMAT_OF(typename Type, ::std::initializer_list<Type>);
struct_CUSTOM_FORMATTER(typename Type, ::std::initializer_list<Type>,
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	},
	static void format(Context& pContext COMMA const ::std::initializer_list<Type>& pValue)
	{
		Formatter<char>::format(pContext COMMA details::FormatTraits::leftSquareBracketSpecifier);
		Formatter<Type>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::initializer_list<Type>::const_iterator;
		for (ConstIterator iterator = pValue.begin() + 1; iterator != pValue.end(); iterator++)
		{
			Formatter<char>::format(pContext COMMA details::FormatTraits::spaceSpecifier);
			Formatter<Type>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA details::FormatTraits::rightSquareBracketSpecifier);
	}
);

#endif

#endif

/**
 * Standard forward list formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_FORWARD_LIST_FORMATTER == 1

#ifndef STD_FORWARD_LIST_FORMATTER
#define STD_FORWARD_LIST_FORMATTER

#include <forward_list>

struct_CUSTOM_FORMAT_OF(typename Type, ::std::forward_list<Type>);
struct_CUSTOM_FORMATTER(typename Type, ::std::forward_list<Type>,
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	},
	static void format(Context& pContext COMMA const ::std::forward_list<Type>& pValue)
	{
		Formatter<char>::format(pContext COMMA details::FormatTraits::leftSquareBracketSpecifier);
		Formatter<Type>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::forward_list<Type>::const_iterator;
		for (ConstIterator iterator = ++pValue.begin(); iterator != pValue.end(); iterator++)
		{
			Formatter<char>::format(pContext COMMA details::FormatTraits::spaceSpecifier);
			Formatter<Type>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA details::FormatTraits::rightSquareBracketSpecifier);
	}
);

#endif

#endif

/**
 * Standard array formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_ARRAY_FORMATTER == 1

#ifndef STD_ARRAY_FORMATTER
#define STD_ARRAY_FORMATTER

#include <array>

struct_CUSTOM_FORMAT_OF(typename Type COMMA typename ::std::size_t tSize, ::std::array<Type COMMA tSize>);
struct_CUSTOM_FORMATTER(typename Type COMMA typename ::std::size_t tSize, ::std::array<Type COMMA tSize>,
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	},
	static void format(Context& pContext COMMA const ::std::array<Type COMMA tSize>& pValue)
	{
		Formatter<char>::format(pContext COMMA details::FormatTraits::leftSquareBracketSpecifier);
		Formatter<Type>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::array<Type COMMA tSize>::const_iterator;
		for (ConstIterator iterator = pValue.cbegin() + 1; iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext COMMA details::FormatTraits::spaceSpecifier);
			Formatter<Type>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA details::FormatTraits::rightSquareBracketSpecifier);
	}
);

#endif

#endif

/**
 * Standard vector formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_VECTOR_FORMATTER == 1

#ifndef STD_VECTOR_FORMATTER
#define STD_VECTOR_FORMATTER

#include <vector>

struct_CUSTOM_FORMAT_OF(typename Type COMMA typename Allocator, ::std::vector<Type COMMA Allocator>);
struct_CUSTOM_FORMATTER(typename Type COMMA typename Allocator, ::std::vector<Type COMMA Allocator>,
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	},
	static void format(Context& pContext COMMA const ::std::vector<Type COMMA Allocator>& pValue)
	{
		Formatter<char>::format(pContext COMMA details::FormatTraits::leftSquareBracketSpecifier);
		Formatter<Type>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::vector<Type COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = pValue.cbegin() + 1; iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext COMMA details::FormatTraits::spaceSpecifier);
			Formatter<Type>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA details::FormatTraits::rightSquareBracketSpecifier);
	}
);

#endif

#endif

/**
 * Standard list formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_LIST_FORMATTER == 1

#ifndef STD_LIST_FORMATTER
#define STD_LIST_FORMATTER

#include <list>

struct_CUSTOM_FORMAT_OF(typename Type COMMA typename Allocator, ::std::list<Type COMMA Allocator>);
struct_CUSTOM_FORMATTER(typename Type COMMA typename Allocator, ::std::list<Type COMMA Allocator>,
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	},
	static void format(Context& pContext COMMA const ::std::list<Type COMMA Allocator>& pValue)
	{
		Formatter<char>::format(pContext COMMA details::FormatTraits::leftSquareBracketSpecifier);
		Formatter<Type>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::list<Type COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext COMMA details::FormatTraits::spaceSpecifier);
			Formatter<Type>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA details::FormatTraits::rightSquareBracketSpecifier);
	}
);

#endif

#endif

/**
 * Standard deque formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_DEQUE_FORMATTER == 1

#ifndef STD_DEQUE_FORMATTER
#define STD_DEQUE_FORMATTER

#include <deque>

struct_CUSTOM_FORMAT_OF(typename Type COMMA typename Allocator, ::std::deque<Type COMMA Allocator>);
struct_CUSTOM_FORMATTER(typename Type COMMA typename Allocator, ::std::deque<Type COMMA Allocator>,
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	},
	static void format(Context& pContext COMMA const ::std::deque<Type COMMA Allocator>& pValue)
	{
		Formatter<char>::format(pContext COMMA details::FormatTraits::leftSquareBracketSpecifier);
		Formatter<Type>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::deque<Type COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = pValue.cbegin() + 1; iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext COMMA details::FormatTraits::spaceSpecifier);
			Formatter<Type>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA details::FormatTraits::rightSquareBracketSpecifier);
	}
);

#endif

#endif

/**
 * Standard set formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_SET_FORMATTER == 1

#ifndef STD_SET_FORMATTER
#define STD_SET_FORMATTER

#include <set>

struct_CUSTOM_FORMAT_OF(typename Type COMMA typename Compare COMMA typename Allocator, ::std::set<Type COMMA Compare COMMA Allocator>);
struct_CUSTOM_FORMATTER(typename Type COMMA typename Compare COMMA typename Allocator, ::std::set<Type COMMA Compare COMMA Allocator>,
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	},
	static void format(Context& pContext COMMA const ::std::set<Type COMMA Compare COMMA Allocator>& pValue)
	{
		Formatter<char>::format(pContext COMMA details::FormatTraits::leftSquareBracketSpecifier);
		Formatter<Type>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::set<Type COMMA Compare COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext COMMA details::FormatTraits::spaceSpecifier);
			Formatter<Type>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA details::FormatTraits::rightSquareBracketSpecifier);
	}
);

#endif

#endif

/**
 * Standard unordered set formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_UNORDERED_SET_FORMATTER == 1

#ifndef STD_UNORDERED_SET_FORMATTER
#define STD_UNORDERED_SET_FORMATTER

#include <unordered_set>

struct_CUSTOM_FORMAT_OF(typename Value COMMA typename Hash COMMA typename Predicate COMMA typename Allocator, ::std::unordered_set<Value COMMA Hash COMMA Predicate COMMA Allocator>);
struct_CUSTOM_FORMATTER(typename Value COMMA typename Hash COMMA typename Predicate COMMA typename Allocator, ::std::unordered_set<Value COMMA Hash COMMA Predicate COMMA Allocator>,
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	},
	static void format(Context& pContext COMMA const ::std::unordered_set<Value COMMA Hash COMMA Predicate COMMA Allocator>& pValue)
	{
		Formatter<char>::format(pContext COMMA details::FormatTraits::leftSquareBracketSpecifier);
		Formatter<Value>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::unordered_set<Value COMMA Hash COMMA Predicate COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext COMMA details::FormatTraits::spaceSpecifier);
			Formatter<Value>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA details::FormatTraits::rightSquareBracketSpecifier);
	}
);

#endif

#endif

/**
 * Standard pair formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_PAIR_FORMATTER == 1

#ifndef STD_PAIR_FORMATTER
#define STD_PAIR_FORMATTER

#include <utility>

struct_CUSTOM_FORMAT_OF(typename Key COMMA typename Value, ::std::pair<Key COMMA Value>);
struct_CUSTOM_FORMATTER(typename Key COMMA typename Value, ::std::pair<Key COMMA Value>,
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	},
	static void format(Context& pContext COMMA const ::std::pair<Key COMMA Value>& pValue)
	{
		Formatter<char>::format(pContext COMMA details::FormatTraits::leftSquareBracketSpecifier);
		Formatter<Key>::format(pContext COMMA pValue.first);
		Formatter<char>::format(pContext COMMA details::FormatTraits::spaceSpecifier);
		Formatter<Value>::format(pContext COMMA pValue.second);
		Formatter<char>::format(pContext COMMA details::FormatTraits::rightSquareBracketSpecifier);
	}
);

#endif

#endif

/**
 * Standard map formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_MAP_FORMATTER == 1

#ifndef STD_MAP_FORMATTER
#define STD_MAP_FORMATTER

#include <utility>
#include <map>

struct_CUSTOM_FORMAT_OF(typename Key COMMA typename Value COMMA typename Compare COMMA typename Allocator, ::std::map<Key COMMA Value COMMA Compare COMMA Allocator>);
struct_CUSTOM_FORMATTER(typename Key COMMA typename Value COMMA typename Compare COMMA typename Allocator, ::std::map<Key COMMA Value COMMA Compare COMMA Allocator>,
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	},
	static void format(Context& pContext COMMA const ::std::map<Key COMMA Value COMMA Compare COMMA Allocator>& pValue)
	{
		using Pair = typename ::std::pair<Key COMMA Value>;
		Formatter<char>::format(pContext COMMA details::FormatTraits::leftSquareBracketSpecifier);
		Formatter<Pair>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::map<Key COMMA Value COMMA Compare COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext COMMA details::FormatTraits::spaceSpecifier);
			Formatter<Pair>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA details::FormatTraits::rightSquareBracketSpecifier);
	}
);

#endif

#endif

/**
 * Standard unordered map formatter.
 */
#if ENABLE_STD_FORMATTERS == 1 || ENABLE_STD_UNORDERED_MAP_FORMATTER == 1

#ifndef STD_UNORDERED_MAP_FORMATTER
#define STD_UNORDERED_MAP_FORMATTER

#include <utility>
#include <unordered_map>

struct_CUSTOM_FORMAT_OF(typename Key COMMA typename Value COMMA typename Hash COMMA typename Predicate COMMA typename Allocator, ::std::unordered_map<Key COMMA Value COMMA Hash COMMA Predicate COMMA Allocator>);
struct_CUSTOM_FORMATTER(typename Key COMMA typename Value COMMA typename Hash COMMA typename Predicate COMMA typename Allocator, ::std::unordered_map<Key COMMA Value COMMA Hash COMMA Predicate COMMA Allocator>,
	static void parse(Context& pContext)
	{
		PARSE_IGNORE(pContext);
	},
	static void format(Context& pContext COMMA const ::std::unordered_map<Key COMMA Value COMMA Hash COMMA Predicate COMMA Allocator>& pValue)
	{
		using Pair = typename ::std::pair<Key COMMA Value>;
		Formatter<char>::format(pContext COMMA details::FormatTraits::leftSquareBracketSpecifier);
		Formatter<Pair>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::unordered_map<Key COMMA Value COMMA Hash COMMA Predicate COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext COMMA details::FormatTraits::spaceSpecifier);
			Formatter<Pair>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA details::FormatTraits::rightSquareBracketSpecifier);
	}
);

#endif

#endif
