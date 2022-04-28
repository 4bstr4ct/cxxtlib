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

#ifndef FORMAT_CLANG_VERSION
#	if defined(__clang__) && !defined(__ibmxl__)
#		define FORMAT_CLANG_VERSION (__clang_major__ * 100 + __clang_minor__)
#	else
#		define FORMAT_CLANG_VERSION 0
#	endif
#endif

#ifndef FORMAT_GCC_VERSION
#	if defined(__GNUC__) && !defined(__clang__) && !defined(__INTEL_COMPILER) && !defined(__NVCOMPILER)
#		define FORMAT_GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
#	else
#		define FORMAT_GCC_VERSION 0
#	endif
#endif

#ifndef FORMAT_GCC_PRAGMA
#	if FORMAT_GCC_VERSION >= 504
#		define FORMAT_GCC_PRAGMA(arg) _Pragma(arg)
#	else
#		define FORMAT_GCC_PRAGMA(arg)
#	endif
#endif

#ifndef FORMAT_ICC_VERSION
#	ifdef __ICL
#		define FORMAT_ICC_VERSION __ICL
#	elif defined(__INTEL_COMPILER)
#		define FORMAT_ICC_VERSION __INTEL_COMPILER
#	else
#		define FORMAT_ICC_VERSION 0
#	endif
#endif

#ifndef FORMAT_NVCOMPILER_VERSION
#	ifdef __NVCOMPILER
#		define FORMAT_NVCOMPILER_VERSION (__NVCOMPILER_MAJOR__ * 100 + __NVCOMPILER_MINOR__)
#	else
#		define FORMAT_NVCOMPILER_VERSION 0
#	endif
#endif

#ifndef FORMAT_NVCC
#	ifdef __NVCC__
#		define FORMAT_NVCC __NVCC__
#	else
#		define FORMAT_NVCC 0
#	endif
#endif

#ifndef FORMAT_MSC_VER
#	ifdef _MSC_VER
#		define FORMAT_MSC_VER _MSC_VER
#	else
#		define FORMAT_MSC_VER 0
#	endif
#endif

#ifndef FORMAT_MSC_WARNING
#	ifdef _MSC_VER
#		define FORMAT_MSC_WARNING(...) __pragma(warning(__VA_ARGS__))
#	else
#		define FORMAT_MSC_WARNING(...)
#	endif
#endif

#ifndef FORMAT_HAS_FEATURE
#	ifdef __has_feature
#		define FORMAT_HAS_FEATURE(x) __has_feature(x)
#	else
#		define FORMAT_HAS_FEATURE(x) 0
#	endif
#endif

#ifndef FORMAT_CPLUSPLUS
#	ifdef _MSVC_LANG
#		define FORMAT_CPLUSPLUS _MSVC_LANG
#	else
#		define FORMAT_CPLUSPLUS __cplusplus
#	endif
#endif

#ifndef FORMAT_HAS_CPP_ATTRIBUTE
#	ifdef __has_cpp_attribute
#		define FORMAT_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#	else
#		define FORMAT_HAS_CPP_ATTRIBUTE(x) 0
#	endif
#endif

#ifndef FORMAT_HAS_CPP14_ATTRIBUTE
#	define FORMAT_HAS_CPP14_ATTRIBUTE(attribute) (FORMAT_CPLUSPLUS >= 201402L && FORMAT_HAS_CPP_ATTRIBUTE(attribute))
#endif

#ifndef FORMAT_HAS_CPP17_ATTRIBUTE
#	define FORMAT_HAS_CPP17_ATTRIBUTE(attribute) (FORMAT_CPLUSPLUS >= 201703L && FORMAT_HAS_CPP_ATTRIBUTE(attribute))
#endif

#ifndef FORMAT_USE_CONSTEXPR
#	define FORMAT_USE_CONSTEXPR (FORMAT_HAS_FEATURE(cxx_relaxed_constexpr) || FORMAT_MSC_VER >= 1912 || (FORMAT_GCC_VERSION >= 600 && __cplusplus >= 201402L)) && !FORMAT_NVCC && !FORMAT_ICC_VERSION
#endif

#ifdef FORMAT_USE_CONSTEXPR
#	if FORMAT_USE_CONSTEXPR
#		define FORMAT_CONSTEXPR constexpr
#		define FORMAT_CONSTEXPR_DECL constexpr
#	else
#		define FORMAT_CONSTEXPR
#		define FORMAT_CONSTEXPR_DECL
#	endif
#endif

#ifndef FORMAT_NOEXCEPT
#	if defined(_MSC_VER) && (_MSC_VER < 1900)
#		define FORMAT_NOEXCEPT _NOEXCEPT
#	else
#		define FORMAT_NOEXCEPT noexcept
#	endif
#endif

#ifndef FORMAT_INLINE
# 	if FORMAT_GCC_VERSION || FORMAT_CLANG_VERSION
#		define FORMAT_INLINE inline __attribute__((always_inline))
#	else
#		define FORMAT_INLINE inline
#	endif
#endif

#ifndef FORMAT_NOINLINE
#	if FORMAT_GCC_VERSION || FORMAT_CLANG_VERSION
#		define FORMAT_NOINLINE __attribute__((noinline))
#	else
#		define FORMAT_NOINLINE
#	endif
#endif

#ifndef FORMAT_NORETURN
#	if CXXTLIB_FORMAT_EXCEPTIONS && FORMAT_HAS_CPP_ATTRIBUTE(noreturn) && !FORMAT_MSC_VER && !FORMAT_NVCC
#		define FORMAT_NORETURN [[noreturn]]
#	else
#		define FORMAT_NORETURN
#	endif
#endif

#ifndef FORMAT_NODISCARD
#	if FORMAT_HAS_CPP17_ATTRIBUTE(nodiscard)
#		define FORMAT_NODISCARD [[nodiscard]]
#	else
#		define FORMAT_NODISCARD
#	endif
#endif

#ifndef FORMAT_DEPRECATED
#	if FORMAT_HAS_CPP14_ATTRIBUTE(deprecated) || FORMAT_MSC_VER >= 1900
#		define FORMAT_DEPRECATED [[deprecated]]
#	else
#		if (defined(__GNUC__) && !defined(__LCC__)) || defined(__clang__)
#			define FORMAT_DEPRECATED __attribute__((deprecated))
#		elif FORMAT_MSC_VER
#			define FORMAT_DEPRECATED __declspec(deprecated)
#		else
#			define FORMAT_DEPRECATED /* deprecated */
#		endif
#	endif
#endif

#ifndef FORMAT_DEBUG
#	if _MSC_VER
#		define FORMAT_DEBUG _DEBUG
#	else
#		define FORMAT_DEBUG NDEBUG
#	endif
#endif

#ifndef FORMAT_COMMA
#	define FORMAT_COMMA ,
#endif

#ifndef COMMA
#	define COMMA FORMAT_COMMA
#endif

#ifndef NONE
#	define NONE
#endif

namespace cformat
{
	namespace details
	{
		using null = decltype(nullptr);

		using int8 = signed char;

		using uint8 = unsigned char;
		
		using int16 = signed short;

		using uint16 = unsigned short;

		using int32 = signed int;
		
		using uint32 = unsigned int;

		using int64 = signed long long;
		
		using uint64 = unsigned long long;

		using ldouble = long double;

		namespace ascii
		{
			static FORMAT_INLINE FORMAT_CONSTEXPR uint32 length(const char* pString) FORMAT_NOEXCEPT
			{
				uint32 count = 0;
				while (pString[count]) count++;
				return count;
			}

			static FORMAT_INLINE FORMAT_CONSTEXPR char* fill(char* pString, char pValue, uint32 pCount) FORMAT_NOEXCEPT
			{
				char* head = pString;
				for (uint32 index = 0; index < pCount; index++) head[index] = pValue;
				return pString;
			}

			static FORMAT_INLINE FORMAT_CONSTEXPR char* copy(char* destination, const char* source) FORMAT_NOEXCEPT
			{
				char* head = destination;
				while((*destination++ = *source++) != '\0');
				return head;
			}

			static FORMAT_INLINE FORMAT_CONSTEXPR char* copy(char* destination, const char* source, uint32 pCount) FORMAT_NOEXCEPT
			{
				char* head = destination;
				for (uint32 index = 0; index < pCount; index++) destination[index] = source[index];
				return head;
			}
		}

		template<typename Type>
		struct AddConst
		{
		public:
			using ValueType = const Type;
		};

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

		template<typename Type>
		struct AddVolatile
		{
		public:
			using ValueType = volatile Type;
		};
		
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

		template<typename Type>
		struct AddConstVolatile
		{
		public:
			using ValueType = typename AddConst<typename AddVolatile<Type>::ValueType>::ValueType;
		};

		template<typename Type>
		struct RemoveConstVolatile
		{
		public:
			using ValueType = typename RemoveConst<typename RemoveVolatile<Type>::ValueType>::ValueType;
		};

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

		template<typename Type, Type tValue>
		struct IntegralConstant
		{
		public:
			using ValueType = Type;

		public:
			static FORMAT_CONSTEXPR const Type sValue = tValue;
		};

		template<bool tValue>
		using BoolConstant = IntegralConstant<bool, tValue>;

		using TrueType = IntegralConstant<bool, true>;

		using FalseType = IntegralConstant<bool, false>;

		template<bool, typename, typename>
		struct Conditional;

		template<typename>
		struct IsLValueReference;

		template<typename>
		struct IsRValueReference;

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
			: public Conditional<First::sValue, First, Second>::ValueType
		{ };

		template<typename First, typename Second, typename Third, typename... Other>
		struct Or<First, Second, Third, Other...>
			: public Conditional<First::sValue, First, Or<Second, Third, Other...>>::ValueType
		{ };

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
			: public Conditional<First::sValue, Second, First>::ValueType
		{ };

		template<typename First, typename Second, typename Third, typename... Other>
		struct And<First, Second, Third, Other...>
			: public Conditional<First::sValue, And<Second, Third, Other...>, First>::ValueType
		{ };

		template<typename Type>
		struct Not
			: public BoolConstant<!bool(Type::sValue)>
		{ };

		template<typename Type>
		struct Identity
		{
		public:
			using ValueType = Type;
		};

		template<typename>
		struct IsConst
			: public FalseType
		{ };

		template<typename Type>
		struct IsConst<const Type>
			: public TrueType
		{ };

		template<typename>
		struct IsVolatile
			: public FalseType
		{ };

		template<typename Type>
		struct IsVolatile<volatile Type>
			: public TrueType
		{ };

		template<typename>
		struct IsConstVolatile
			: public FalseType
		{ };

		template<typename Type>
		struct IsConstVolatile<const volatile Type>
			: public TrueType
		{ };

		template<typename Type>
		struct IsLiteral
			: public IntegralConstant<bool, __is_literal_type(Type)>
		{ };

		template<typename Type>
		struct IsEmpty
			: public IntegralConstant<bool, __is_empty(Type)>
		{ };

		template<typename Type>
		struct IsPolymorphic
			: public IntegralConstant<bool, __is_polymorphic(Type)>
		{ };

#if FORMAT_CPLUSPLUS >= 201402L
		template<typename Type>
		struct IsFinal
			: public IntegralConstant<bool, __is_final(Type)>
		{ };
#endif

		template<typename Type>
		struct IsAbstract
			: public IntegralConstant<bool, __is_abstract(Type)>
		{ };

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

		template<typename>
		struct IsArray
			: public FalseType
		{ };

		template<typename Type, uint32 tSize>
		struct IsArray<Type[tSize]>
			: public TrueType
		{ };

		template<typename Type>
		struct IsArray<Type[]>
			: public TrueType
		{ };

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

		template<typename Type>
		struct IsEnum
			: public BoolConstant<__is_enum(Type)>
		{ };

		template<typename Type>
		struct IsUnion
			: public BoolConstant<__is_union(Type)>
		{ };

		template<typename Type>
		struct IsClass
			: public BoolConstant<__is_class(Type)>
		{ };

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

		template<typename Type>
		struct IsReference
			: public Or<IsLValueReference<Type>, IsRValueReference<Type>>
		{ };

		template<typename Type>
		struct IsObject
			: public Not<Or<IsFunction<Type>, IsReference<Type>, IsVoid<Type>>>
		{ };

		template<typename Type>
		struct IsReferenceable
			: public Or<IsObject<Type>, IsReference<Type>>
		{ };

		template<typename Result, typename... Arguments>
		struct IsReferenceable<Result(Arguments...)>
			: public TrueType
		{ };

		template<typename>
		struct IsLValueReference
			: public FalseType
		{ };

		template<typename Type>
		struct IsLValueReference<Type&>
			: public TrueType
		{ };

		template<typename Type, bool = IsReferenceable<Type>::sValue>
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

		template<typename>
		struct IsRValueReference
			: public FalseType
		{ };

		template<typename Type>
		struct IsRValueReference<Type&&>
			: public TrueType
		{ };

		template<typename Type, bool = IsReferenceable<Type>::sValue>
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

		template<bool, typename Type = void>
		struct EnableIf { };

		template<typename Type>
		struct EnableIf<true, Type>
		{
		public:
			using ValueType = Type;
		};

		template<typename Type>
		static FORMAT_INLINE FORMAT_CONSTEXPR typename EnableIf<!IsLValueReference<Type>::sValue, Type&&>::ValueType forward(typename Identity<Type>::ValueType& pValue) FORMAT_NOEXCEPT
		{
			return static_cast<Type&&>(pValue);
		}

		template<typename Type>
		static FORMAT_INLINE FORMAT_CONSTEXPR typename EnableIf<!IsLValueReference<Type>::sValue, Type&&>::ValueType forward(typename Identity<Type>::ValueType&& pValue) FORMAT_NOEXCEPT
		{
			return static_cast<Type&&>(pValue);
		}

		template<typename Type>
		static FORMAT_INLINE FORMAT_CONSTEXPR typename EnableIf<IsLValueReference<Type>::sValue, Type>::ValueType forward(typename Identity<Type>::ValueType pValue) FORMAT_NOEXCEPT
		{
			return pValue;
		}

		template<typename Type>
		static FORMAT_INLINE FORMAT_CONSTEXPR typename EnableIf<IsLValueReference<Type>::sValue, Type>::ValueType forward(typename RemoveReference<Type>::ValueType&& pValue) FORMAT_NOEXCEPT = delete;

		template<typename Type>
		static FORMAT_INLINE FORMAT_CONSTEXPR typename RemoveReference<Type>::ValueType&& move(Type&& pValue) FORMAT_NOEXCEPT
		{
			return static_cast<typename RemoveReference<Type>::ValueType&&>(pValue);
		}
	}

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
		static FORMAT_CONSTEXPR const FormatArgumentType sValue = FormatArgumentType::None;
	};

	#define __struct_INTERNAL_FORMAT_OF(Dependencies, Type, FType) \
	template<Dependencies> \
	struct FormatOf<Type> \
	{ \
	public: \
		static FORMAT_CONSTEXPR const FormatArgumentType sValue = FType; \
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
		static FORMAT_INLINE FORMAT_CONSTEXPR void parseIgnore(Context& pContext) FORMAT_NOEXCEPT
		{
			for (; *pContext != '}'; pContext++);
			pContext++;
		}
	};

	template<typename Type, typename Enable = void>
	struct Formatter
	{
		static_assert(FormatOf<Type>::sValue != FormatArgumentType::None, "Provided type does not have a formatter!");
	};

	template<typename Type>
	using FormatterEnabler = typename details::EnableIf
	<
		details::BoolConstant
		<
			details::IntegralConstant
			<
				FormatArgumentType,
				FormatOf<Type>::sValue
			>::sValue != FormatArgumentType::None
		>::sValue
	>::ValueType;

	#define __struct_INTERNAL_FORMATTER(Dependencies, Type, PFunc, FFunc) \
	template<Dependencies> \
	struct Formatter<Type, FormatterEnabler<Type>> \
	{ \
	public: \
		template<typename Context> \
		static PFunc \
			\
		template<typename Context> \
		static FFunc \
	}

	__struct_INTERNAL_FORMATTER(NONE, bool,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA bool pValue) FORMAT_NOEXCEPT
		{
			pContext.append(pValue ? "true" : "false" COMMA pValue ? 4u : 5u);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, char,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA char pValue) FORMAT_NOEXCEPT
		{
			pContext.append(pValue);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, details::int8,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA details::int8 pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 5u;
			char buffer[size] = { };
			const details::int32 written = ::snprintf(buffer COMMA size COMMA "%d" COMMA pValue);
			
			if (written >= 0)
			{
				pContext.append(buffer COMMA written);
			}
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, details::uint8,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA details::uint8 pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 5u;
			char buffer[size] = { };
			const details::int32 written = ::snprintf(buffer COMMA size COMMA "%u" COMMA pValue);
			
			if (written >= 0)
			{
				pContext.append(buffer COMMA written);
			}
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, details::int16,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA details::int16 pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 7u;
			char buffer[size] = { };
			const details::int32 written = ::snprintf(buffer COMMA size COMMA "%d" COMMA pValue);
			
			if (written >= 0)
			{
				pContext.append(buffer COMMA written);
			}
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, details::uint16,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA details::uint16 pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 7u;
			char buffer[size] = { };
			const details::int32 written = ::snprintf(buffer COMMA size COMMA "%u" COMMA pValue);
			
			if (written >= 0)
			{
				pContext.append(buffer COMMA written);
			}
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, details::int32,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA details::int32 pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 12u;
			char buffer[size] = { };
			const details::int32 written = ::snprintf(buffer COMMA size COMMA "%d" COMMA pValue);
			
			if (written >= 0)
			{
				pContext.append(buffer COMMA written);
			}
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, details::uint32,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA details::uint32 pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 12u;
			char buffer[size] = { };
			const details::int32 written = ::snprintf(buffer COMMA size COMMA "%u" COMMA pValue);
			
			if (written >= 0)
			{
				pContext.append(buffer COMMA written);
			}
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, details::int64,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA details::int64 pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 21u;
			char buffer[size] = { };
			const details::int32 written = ::snprintf(buffer COMMA size COMMA "%lld" COMMA pValue);
			
			if (written >= 0)
			{
				pContext.append(buffer COMMA written);
			}
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, details::uint64,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA details::uint64 pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 21u;
			char buffer[size] = { };
			const details::int32 written = ::snprintf(buffer COMMA size COMMA "%llu" COMMA pValue);
			
			if (written >= 0)
			{
				pContext.append(buffer COMMA written);
			}
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, float,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA float pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 25u;
			char buffer[size] = { };
			const details::int32 written = ::snprintf(buffer COMMA size COMMA "%f" COMMA pValue);
			
			if (written >= 0)
			{
				pContext.append(buffer COMMA written);
			}
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, double,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA double pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 25u;
			char buffer[size] = { };
			const details::int32 written = ::snprintf(buffer COMMA size COMMA "%f" COMMA pValue);
			
			if (written >= 0)
			{
				pContext.append(buffer COMMA written);
			}
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, details::ldouble,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA details::ldouble pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 26u;
			char buffer[size] = { };
			const details::int32 written = ::snprintf(buffer COMMA size COMMA "%Lf" COMMA pValue);
			
			if (written >= 0)
			{
				pContext.append(buffer COMMA written);
			}
		}
	);

	__struct_INTERNAL_FORMATTER(typename Type, Type*,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA Type* pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 19u;
			char buffer[size] = { };
			const details::int32 written = ::snprintf(buffer COMMA size COMMA "0x%p" COMMA (void*)pValue);
			
			if (written >= 0)
			{
				pContext.append(buffer COMMA written);
			}
		}
	);

	__struct_INTERNAL_FORMATTER(typename Type, const Type*,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA const Type* pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 19u;
			char buffer[size] = { };
			const details::int32 written = ::snprintf(buffer COMMA size COMMA "0x%p" COMMA (const void*)pValue);
			
			if (written >= 0)
			{
				pContext.append(buffer COMMA written);
			}
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, details::null,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA details::null pValue) FORMAT_NOEXCEPT
		{
			pContext.append("nullptr" COMMA 7u);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, const char*,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA const char* pValue) FORMAT_NOEXCEPT
		{
			if (pValue)
			{
				pContext.append(pValue COMMA details::ascii::length(pValue));
			}
			else
			{
				pContext.append("nullptr" COMMA 7u);
			}
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, const char[],
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA const char pValue[]) FORMAT_NOEXCEPT
		{
			pContext.append(pValue COMMA details::ascii::length(pValue));
		}
	);

	__struct_INTERNAL_FORMATTER(typename details::uint32 tSize, const char[tSize],
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA const char pValue[tSize]) FORMAT_NOEXCEPT
		{
			pContext.append(pValue COMMA tSize - 1);
		}
	);

	template<typename Reader, typename Writer>
	static FORMAT_INLINE FORMAT_CONSTEXPR void formatHandle(Reader& pReader, Writer& pWriter) FORMAT_NOEXCEPT
	{
		pWriter.append(pReader.iterator(), pReader.size());
	}

	template<typename Reader, typename Writer, typename Argument, typename... Arguments>
	static FORMAT_INLINE FORMAT_CONSTEXPR void formatHandle(Reader& pReader, Writer& pWriter, Argument&& pArgument, Arguments&&... pArguments) FORMAT_NOEXCEPT
	{
		const char* previous = pReader.iterator();
		for (; *pReader != '{' && pReader.iterator() != pReader.end(); pReader++);

		if (*pReader == '{')
		{
			pWriter.append(previous, (details::uint32)(pReader.iterator() - previous));
			using DRefArgument = typename details::RemoveVolatile<typename details::RemoveReference<Argument>::ValueType>::ValueType;
			Formatter<DRefArgument>::template parse<Reader>(pReader);
			Formatter<DRefArgument>::template format<Writer>(pWriter, pArgument);
		}

		formatHandle<Reader, Writer>(pReader, pWriter, pArguments...);
	}

	class Reader
	{
	private:
		const char* mIterator;
		const char* mBegin;
		const char* mEnd;
	
	public:
		explicit Reader(const char* pIterator, const char* pBegin, const char* pEnd) FORMAT_NOEXCEPT
			: mIterator(pIterator), mBegin(pBegin), mEnd(pEnd)
		{ }

	public:
		FORMAT_INLINE FORMAT_CONSTEXPR details::uint32 size() const FORMAT_NOEXCEPT
		{
			return static_cast<details::uint32>(this->mEnd - this->mIterator);
		}

		FORMAT_INLINE FORMAT_CONSTEXPR const char* iterator() const FORMAT_NOEXCEPT
		{
			return this->mIterator;
		}

		FORMAT_INLINE FORMAT_CONSTEXPR const char* begin() const FORMAT_NOEXCEPT
		{
			return this->mBegin;
		}

		FORMAT_INLINE FORMAT_CONSTEXPR const char* end() const FORMAT_NOEXCEPT
		{
			return this->mEnd;
		}

	public:
		FORMAT_INLINE Reader operator +(details::int32 pOffset) FORMAT_NOEXCEPT
		{
			Reader reader = Reader(this->mIterator + pOffset, this->mBegin, this->mEnd);
			return reader;
		}

		FORMAT_INLINE FORMAT_CONSTEXPR Reader& operator +=(details::int32 pOffset) FORMAT_NOEXCEPT
		{
			this->mIterator += pOffset;
			return *this;
		}
		
		FORMAT_INLINE FORMAT_CONSTEXPR Reader& operator ++() FORMAT_NOEXCEPT
		{
			this->mIterator++;
			return *this;
		}

		FORMAT_INLINE Reader operator ++(details::int32) FORMAT_NOEXCEPT
		{
			Reader reader = Reader(this->mIterator, this->mBegin, this->mEnd);
			++(*this);
			return reader;
		}

		FORMAT_INLINE Reader operator -(details::int32 pOffset) FORMAT_NOEXCEPT
		{
			Reader reader = Reader(this->mIterator - pOffset, this->mBegin, this->mEnd);
			return reader;
		}

		FORMAT_INLINE FORMAT_CONSTEXPR Reader& operator -=(details::int32 pOffset) FORMAT_NOEXCEPT
		{
			this->mIterator -= pOffset;
			return *this;
		}

		FORMAT_INLINE FORMAT_CONSTEXPR Reader& operator --() FORMAT_NOEXCEPT
		{
			this->mIterator--;
			return *this;
		}

		FORMAT_INLINE Reader operator --(details::int32) FORMAT_NOEXCEPT
		{
			Reader reader = Reader(this->mIterator, this->mBegin, this->mEnd);
			--(*this);
			return reader;
		}

		FORMAT_INLINE FORMAT_CONSTEXPR const char& operator *() const FORMAT_NOEXCEPT
		{
			return *this->mIterator;
		}

		FORMAT_INLINE FORMAT_CONSTEXPR bool operator ==(const Reader& pOther) const FORMAT_NOEXCEPT
		{
			return this->mIterator == pOther.iterator() && this->mBegin == pOther.begin() && this->mEnd == pOther.end();
		}

		FORMAT_INLINE FORMAT_CONSTEXPR bool operator !=(const Reader& pOther) const FORMAT_NOEXCEPT
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
		explicit HeapWriter(details::uint32 pCapacity = 4u) FORMAT_NOEXCEPT
			: mData(nullptr), mSize(0), mCapacity(pCapacity)
		{
			allocate(pCapacity);
		}

	private:
		FORMAT_INLINE void allocate(details::uint32 pCapacity) FORMAT_NOEXCEPT
		{
			this->mCapacity = pCapacity;
			this->mData = new char[pCapacity + 1u];
			this->mData[this->mSize] = details::move('\0');
		}

		FORMAT_INLINE void reallocate(details::uint32 pCapacity) FORMAT_NOEXCEPT
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
		FORMAT_INLINE FORMAT_CONSTEXPR details::uint32 size() const FORMAT_NOEXCEPT
		{
			return this->mSize;
		}

		FORMAT_INLINE void FORMAT_CONSTEXPR append(char pChar) FORMAT_NOEXCEPT
		{
			if (this->mSize + 1 > this->mCapacity)
				reallocate(this->mCapacity + this->mCapacity / 2);
			
			this->mData[this->mSize++] = pChar;
			this->mData[this->mSize] = '\0';
		}

		FORMAT_INLINE FORMAT_CONSTEXPR void append(const char* const pData, details::uint32 pSize) FORMAT_NOEXCEPT
		{
			if (this->mSize + pSize > this->mCapacity)
				reallocate(pSize + this->mCapacity + this->mCapacity / 2);

			for (details::uint32 i = 0; i < pSize; i++)
				this->mData[this->mSize + i] = pData[i];

			this->mData[this->mSize += pSize] = '\0';
		}

		FORMAT_INLINE FORMAT_CONSTEXPR char* get() FORMAT_NOEXCEPT
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
		explicit StackWriter(char* pData) FORMAT_NOEXCEPT
			: mData(pData), mSize(0)
		{ }

	public:
		FORMAT_INLINE FORMAT_CONSTEXPR details::uint32 size() const FORMAT_NOEXCEPT
		{
			return this->mSize;
		}
		
		FORMAT_INLINE FORMAT_CONSTEXPR void append(char pChar) FORMAT_NOEXCEPT
		{
			if (this->mSize + 1u <= tCapacity)
				this->mData[this->mSize++] = pChar;
		}

		FORMAT_INLINE FORMAT_CONSTEXPR void append(const char* const pData, details::uint32 pSize) FORMAT_NOEXCEPT
		{
			if (this->mSize + pSize <= tCapacity)
			{
				for (details::uint32 i = 0; i < pSize; i++)
					this->mData[this->mSize + i] = pData[i];
				
				this->mSize += pSize;
			}
		}

		FORMAT_INLINE FORMAT_CONSTEXPR char* get() FORMAT_NOEXCEPT
		{
			this->mData[this->mSize] = '\0';
			return this->mData;
		}
	};

	/**
	 * Formats a dynamic cstring and returns a pointer to it. Note that neither this methods, nor any underlying structures and funtions deallocate
	 * this formatted cstring (the result). It is users responsibility to deallocate result cstring after they finish working with it. User can use
	 * cleanup() function to deallocate memory or store this pointer to formatted cstring inside a smart pointer.
	 */
	template<typename... Arguments>
	static FORMAT_INLINE FORMAT_CONSTEXPR char* format(const char* const pPattern, Arguments&&... pArguments) FORMAT_NOEXCEPT
	{
		const details::uint32 patternLength = details::ascii::length(pPattern);
		Reader reader = Reader(pPattern, pPattern, pPattern + patternLength);
		HeapWriter writer = HeapWriter(patternLength + sizeof...(pArguments) * 2);
		formatHandle<Reader, HeapWriter, Arguments...>(reader, writer, details::forward<Arguments>(pArguments)...);
		return writer.get();
	}

	/**
	 * Returns the length of chars written to the buffer.
	 */
	template<details::uint32 tSize, typename... Arguments>
	static FORMAT_INLINE FORMAT_CONSTEXPR details::uint32 format(char* pBuffer, const char* const pPattern, Arguments&&... pArguments) FORMAT_NOEXCEPT
	{
		Reader reader = Reader(pPattern, pPattern, pPattern + details::ascii::length(pPattern));
		StackWriter<tSize> writer = StackWriter<tSize>(pBuffer);
		formatHandle<Reader, StackWriter<tSize>, Arguments...>(reader, writer, details::forward<Arguments>(pArguments)...);
		return writer.size();
	}

	/**
	 * Should only be used when default format function is used. Default format method creates formatted string on heap
	 * and returns it. It does not handle memory deallocation of the formatted string. That is handled by this function.
	 */
	static FORMAT_INLINE void cleanup(char* pFormatted) FORMAT_NOEXCEPT
	{
		delete[] pFormatted;
	}

 	/**
 	 * Resets every char in the array to termination character - cleans the string.
	 * Should be mainly used with stack arrays.
 	 */
	template<details::uint32 tSize>
	static FORMAT_INLINE void cleanup(char* pFormatted) FORMAT_NOEXCEPT
	{
		details::ascii::fill(pFormatted, char(), tSize);
	}

	/**
	 * Formats string and forwards it to any provided stream that supports << operator (cout, ofstream, etc). This method handles formatted cstring
	 * itself and deallocates it at the end of the function.
	 */
	template<typename Stream, typename... Arguments>
	static FORMAT_INLINE FORMAT_CONSTEXPR void print(Stream& pStream, const char* const pPattern, Arguments&&... pArguments) FORMAT_NOEXCEPT
	{
		char* formatted = format<Arguments...>(pPattern, details::forward<Arguments>(pArguments)...);
		pStream << formatted;
		cleanup(formatted);
	}

	template<typename Stream, details::uint32 tSize, typename... Arguments>
	static FORMAT_INLINE FORMAT_CONSTEXPR void print(Stream& pStream, const char* const pPattern, Arguments&&... pArguments) FORMAT_NOEXCEPT
	{
		char formatted[tSize] = { };
		format<tSize, Arguments...>(formatted, pPattern, details::forward<Arguments>(pArguments)...);
		pStream << formatted;
	}
	
	/**
	 * Printing method for c-like streams.
	 */
	template<typename... Arguments>
	static FORMAT_INLINE FORMAT_CONSTEXPR void cprint(::FILE* pStream, const char* const pPattern, Arguments&&... pArguments) FORMAT_NOEXCEPT
	{
		char* formatted = format<Arguments...>(pPattern, details::forward<Arguments>(pArguments)...);
		::fwrite(formatted, sizeof(char), details::ascii::length(formatted), pStream);
		cleanup(formatted);
	}

	template<details::uint32 tSize, typename... Arguments>
	static FORMAT_INLINE FORMAT_CONSTEXPR void cprint(::FILE* pStream, const char* const pPattern, Arguments&&... pArguments) FORMAT_NOEXCEPT
	{
		char formatted[tSize] = { };
		format<tSize, Arguments...>(formatted, pPattern, details::forward<Arguments>(pArguments)...);
		::fwrite(formatted, sizeof(char), details::ascii::length(formatted), pStream);
	}

	template<typename Type>
	struct SpecifierOf
	{
	public:
		static FORMAT_CONSTEXPR const char sValue = ' ';
	};

	#define __struct_INTERNAL_SPECIFIER_OF(Dependencies, Type, Specifier) \
	template<Dependencies> \
	struct SpecifierOf<Type> \
	{ \
	public: \
		static FORMAT_CONSTEXPR const char sValue = Specifier; \
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
	static FORMAT_INLINE FORMAT_CONSTEXPR const char* precision(char* pBuffer, Type pValue, details::uint32 pPre, details::uint32 pPost) FORMAT_NOEXCEPT
	{
		char temp[10] { };
		details::uint32 count = ::snprintf(temp + 1, 9, "%u.%u", pPre, pPost);

		if (count <= 0)
		{
			return nullptr;
		}
		
		temp[0] = '%';
		temp[++count] = SpecifierOf<Type>::sValue;
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

/**
 * Helper macros and cleanup.
 */
#undef __struct_INTERNAL_FORMAT_OF
#undef __struct_INTERNAL_FORMATTER
#undef __struct_INTERNAL_SPECIFIER_OF

#define PARSE_IGNORE(pContext) \
for (; *pContext != '}'; pContext++); \
pContext++;

#define struct_CUSTOM_FORMAT_OF(Dependencies, Type) \
namespace cformat \
{ \
	template<Dependencies> \
	struct FormatOf<Type> \
	{ \
	public: \
		static FORMAT_CONSTEXPR const FormatArgumentType sValue = FormatArgumentType::Custom; \
	}; \
}

#define struct_CUSTOM_FORMATTER(Dependencies, Type, PFunc, FFunc) \
namespace cformat \
{ \
	template<Dependencies> \
	struct Formatter<Type, FormatterEnabler<Type>> \
	{ \
	public: \
		template<typename Context> \
		static PFunc \
			\
		template<typename Context> \
		static FFunc \
	}; \
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
	FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA const ::std::basic_string<Char COMMA Traits COMMA Allocator>& pValue) FORMAT_NOEXCEPT
	{
		pContext.append(pValue.data() COMMA static_cast<details::uint32>(pValue.size()));
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
	FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA const ::std::initializer_list<Type>& pValue) FORMAT_NOEXCEPT
	{
		Formatter<char>::format(pContext COMMA '[');
		Formatter<Type>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::initializer_list<Type>::const_iterator;
		for (ConstIterator iterator = pValue.begin() + 1; iterator != pValue.end(); iterator++)
		{
			Formatter<char>::format(pContext COMMA ' ');
			Formatter<Type>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA ']');
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
	FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA const ::std::forward_list<Type>& pValue) FORMAT_NOEXCEPT
	{
		Formatter<char>::format(pContext COMMA '[');
		Formatter<Type>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::forward_list<Type>::const_iterator;
		for (ConstIterator iterator = ++pValue.begin(); iterator != pValue.end(); iterator++)
		{
			Formatter<char>::format(pContext COMMA ' ');
			Formatter<Type>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA ']');
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
	FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA const ::std::array<Type COMMA tSize>& pValue) FORMAT_NOEXCEPT
	{
		Formatter<char>::format(pContext COMMA '[');
		Formatter<Type>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::array<Type COMMA tSize>::const_iterator;
		for (ConstIterator iterator = pValue.cbegin() + 1; iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext COMMA ' ');
			Formatter<Type>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA ']');
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
	FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA const ::std::vector<Type COMMA Allocator>& pValue) FORMAT_NOEXCEPT
	{
		Formatter<char>::format(pContext COMMA '[');
		Formatter<Type>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::vector<Type COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = pValue.cbegin() + 1; iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext COMMA ' ');
			Formatter<Type>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA ']');
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
	FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA const ::std::list<Type COMMA Allocator>& pValue) FORMAT_NOEXCEPT
	{
		Formatter<char>::format(pContext COMMA '[');
		Formatter<Type>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::list<Type COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext COMMA ' ');
			Formatter<Type>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA ']');
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
	FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA const ::std::deque<Type COMMA Allocator>& pValue) FORMAT_NOEXCEPT
	{
		Formatter<char>::format(pContext COMMA '[');
		Formatter<Type>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::deque<Type COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = pValue.cbegin() + 1; iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext COMMA ' ');
			Formatter<Type>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA ']');
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
	FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA const ::std::set<Type COMMA Compare COMMA Allocator>& pValue) FORMAT_NOEXCEPT
	{
		Formatter<char>::format(pContext COMMA '[');
		Formatter<Type>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::set<Type COMMA Compare COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext COMMA ' ');
			Formatter<Type>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA ']');
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
	FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA const ::std::unordered_set<Value COMMA Hash COMMA Predicate COMMA Allocator>& pValue) FORMAT_NOEXCEPT
	{
		Formatter<char>::format(pContext COMMA '[');
		Formatter<Value>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::unordered_set<Value COMMA Hash COMMA Predicate COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext COMMA ' ');
			Formatter<Value>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA ']');
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
	FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA const ::std::pair<Key COMMA Value>& pValue) FORMAT_NOEXCEPT
	{
		Formatter<char>::format(pContext COMMA '[');
		Formatter<Key>::format(pContext COMMA pValue.first);
		Formatter<char>::format(pContext COMMA ' ');
		Formatter<Value>::format(pContext COMMA pValue.second);
		Formatter<char>::format(pContext COMMA ']');
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
	FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA const ::std::map<Key COMMA Value COMMA Compare COMMA Allocator>& pValue) FORMAT_NOEXCEPT
	{
		using Pair = typename ::std::pair<Key COMMA Value>;
		Formatter<char>::format(pContext COMMA '[');
		Formatter<Pair>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::map<Key COMMA Value COMMA Compare COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext COMMA ' ');
			Formatter<Pair>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA ']');
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
	FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
	{
		PARSE_IGNORE(pContext);
	},
	FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA const ::std::unordered_map<Key COMMA Value COMMA Hash COMMA Predicate COMMA Allocator>& pValue) FORMAT_NOEXCEPT
	{
		using Pair = typename ::std::pair<Key COMMA Value>;
		Formatter<char>::format(pContext COMMA '[');
		Formatter<Pair>::format(pContext COMMA *pValue.begin());

		using ConstIterator = typename ::std::unordered_map<Key COMMA Value COMMA Hash COMMA Predicate COMMA Allocator>::const_iterator;
		for (ConstIterator iterator = ++pValue.cbegin(); iterator != pValue.cend(); iterator++)
		{
			Formatter<char>::format(pContext COMMA ' ');
			Formatter<Pair>::format(pContext COMMA *iterator);
		}
	
		Formatter<char>::format(pContext COMMA ']');
	}
);

#endif

#endif
 