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
#include <math.h>

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

#if _WIN32
#	define FORMAT_WINDOWS 1
#else
#	define FORMAT_LINUX 1
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
		using byte = unsigned char;

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

			static FORMAT_INLINE FORMAT_CONSTEXPR char* copy(char* pDestination, const char* pSource) FORMAT_NOEXCEPT
			{
				char* head = pDestination;
				while((*pDestination++ = *pSource++) != '\0');
				return head;
			}

			static FORMAT_INLINE FORMAT_CONSTEXPR char* copy(char* pDestination, const char* pSource, uint32 pCount) FORMAT_NOEXCEPT
			{
				char* head = pDestination;
				for (uint32 index = 0; index < pCount; index++) pDestination[index] = pSource[index];
				return head;
			}

			static FORMAT_INLINE FORMAT_CONSTEXPR void reverse(char* pString, uint32 pLength) FORMAT_NOEXCEPT
			{
				int32 start = 0;
				int32 end = pLength - 1u;

				while (start < end)
				{
					char temp = pString[start];
					pString[start++] = pString[end];
					pString[end--] = temp;
				}
			}

			static FORMAT_INLINE FORMAT_CONSTEXPR uint32 itoar(int32 pValue, char* pString, uint32 pBase) FORMAT_NOEXCEPT
			{
				uint32 index = 0;
				bool isNegative = false;

				if (pValue == 0)
				{
					pString[index++] = '0';
					pString[index] = '\0';
					return index;
				}
			
				if (pValue < 0 && pBase == 10u)
				{
					isNegative = true;
					pValue = -pValue;
				}
			
				while (pValue != 0)
				{
					int32 remainder = pValue % pBase;
					pString[index++] = (remainder > 9u) ? (remainder - 10u) + 'a' : remainder + '0';
					pValue /= pBase;
				}
			
				if (isNegative)
					pString[index++] = '-';
			
				pString[index] = '\0';
				return index;
			}
		}

		template<typename OldT>
		struct RemoveConst
		{
		public:
			using Type = OldT;
		};
		
		template<typename OldT>
		struct RemoveConst<const OldT>
		{
		public:
			using Type = OldT;
		};

		template<typename OldT>
		struct RemoveVolatile
		{
		public:
			using Type = OldT;
		};

		template<typename OldT>
		struct RemoveVolatile<volatile OldT>
		{
		public:
			using Type = OldT;
		};

		template<typename OldT>
		struct RemoveConstVolatile
		{
		public:
			using Type = typename RemoveConst<typename RemoveVolatile<OldT>::Type>::Type;
		};

		template<typename OldT>
		struct RemoveReference
		{
		public:
			using Type = OldT;
		};
		
		template<typename OldT>
		struct RemoveReference<OldT&>
		{
		public:
			using Type = OldT;
		};

		template<typename OldT>
		struct RemoveReference<OldT&&>
		{
		public:
			using Type = OldT;
		};

		template<typename OldT, OldT tValue>
		struct IntegralConstant
		{
		public:
			using Type = OldT;

		public:
			static FORMAT_CONSTEXPR const OldT sValue = tValue;

			static FORMAT_INLINE FORMAT_CONSTEXPR const OldT value() FORMAT_NOEXCEPT
			{ return sValue; }
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
			using Type = IfTrue;
		};

		template<typename IfTrue, typename IfFalse>
		struct Conditional<false, IfTrue, IfFalse>
		{
		public:
			using Type = IfFalse;
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
			: public Conditional<First::sValue, First, Second>::Type
		{ };

		template<typename First, typename Second, typename Third, typename... Other>
		struct Or<First, Second, Third, Other...>
			: public Conditional<First::sValue, First, Or<Second, Third, Other...>>::Type
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
			: public Conditional<First::sValue, Second, First>::Type
		{ };

		template<typename First, typename Second, typename Third, typename... Other>
		struct And<First, Second, Third, Other...>
			: public Conditional<First::sValue, And<Second, Third, Other...>, First>::Type
		{ };

		template<typename Type>
		struct Not
			: public BoolConstant<!bool(Type::sValue)>
		{ };

		template<typename OldT>
		struct Identity
		{
		public:
			using Type = OldT;
		};

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
			: public IsVoidHelper<typename RemoveConstVolatile<Type>::Type>
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

		template<typename OldT, bool = IsReferenceable<OldT>::sValue>
		struct AddLValueReferenceHelper
		{
		public:
			using Type = OldT;
		};

		template<typename OldT>
		struct AddLValueReferenceHelper<OldT, true>
		{
		public:
			using Type = OldT&;
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

		template<typename OldT, bool = IsReferenceable<OldT>::sValue>
		struct AddRValueReferenceHelper
		{
		public:
			using Type = OldT;
		};

		template<typename OldT>
		struct AddRValueReferenceHelper<OldT, true>
		{
		public:
			using Type = OldT&&;
		};

		template<typename Type>
		struct AddRValueReference
			: public AddRValueReferenceHelper<Type>
		{ };

		template<bool, typename OldT = void>
		struct EnableIf { };

		template<typename OldT>
		struct EnableIf<true, OldT>
		{
		public:
			using Type = OldT;
		};

		template<typename Type>
		static FORMAT_INLINE FORMAT_CONSTEXPR typename EnableIf<!IsLValueReference<Type>::sValue, Type&&>::Type forward(typename Identity<Type>::Type& pValue) FORMAT_NOEXCEPT
		{
			return static_cast<Type&&>(pValue);
		}

		template<typename Type>
		static FORMAT_INLINE FORMAT_CONSTEXPR typename EnableIf<!IsLValueReference<Type>::sValue, Type&&>::Type forward(typename Identity<Type>::Type&& pValue) FORMAT_NOEXCEPT
		{
			return static_cast<Type&&>(pValue);
		}

		template<typename Type>
		static FORMAT_INLINE FORMAT_CONSTEXPR typename EnableIf<IsLValueReference<Type>::sValue, Type>::Type forward(typename Identity<Type>::Type pValue) FORMAT_NOEXCEPT
		{
			return pValue;
		}

		template<typename Type>
		static FORMAT_INLINE FORMAT_CONSTEXPR typename EnableIf<IsLValueReference<Type>::sValue, Type>::Type forward(typename RemoveReference<Type>::Type&& pValue) FORMAT_NOEXCEPT = delete;

		template<typename Type>
		static FORMAT_INLINE FORMAT_CONSTEXPR typename RemoveReference<Type>::Type&& move(Type&& pValue) FORMAT_NOEXCEPT
		{
			return static_cast<typename RemoveReference<Type>::Type&&>(pValue);
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

		static FORMAT_INLINE FORMAT_CONSTEXPR const FormatArgumentType value() FORMAT_NOEXCEPT
		{ return sValue; }
	};

	#define __struct_INTERNAL_FORMAT_OF(Dependencies, Type, FType) \
	template<Dependencies> \
	struct FormatOf<Type> \
	{ \
	public: \
		static FORMAT_CONSTEXPR const FormatArgumentType sValue = FType; \
		 \
		static FORMAT_INLINE FORMAT_CONSTEXPR FormatArgumentType value() FORMAT_NOEXCEPT \
		{ return sValue; } \
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
		static details::int32 sPrecision;

	public:
		template<typename Context>
		static FORMAT_INLINE FORMAT_CONSTEXPR void parseIgnore(Context& pContext) FORMAT_NOEXCEPT
		{
			for (; *(pContext.current()) != '}'; pContext.next());
			pContext.next();
		}

		template<typename Context>
		static FORMAT_INLINE FORMAT_CONSTEXPR void parseColor(Context& pContext) FORMAT_NOEXCEPT
		{
			if (*(pContext.current()) == 'c' && *(pContext.current() + 1u) == ':')
			{

			}
		}

		template<typename Context>
		static FORMAT_INLINE FORMAT_CONSTEXPR void parsePrecision(Context& pContext) FORMAT_NOEXCEPT
		{
			if (*(pContext.current()) == 'p' && *(pContext.current() + 1u) == ':')
			{
				::sscanf(pContext.current() + 2u, "%d", &sPrecision);
				pContext.move(2u);
			}
		}
	};

	details::int32 FormatterHelpers::sPrecision = 0;

	template<typename Type, typename Enabler = void>
	struct Formatter
	{
		static_assert(FormatOf<Type>::value() != FormatArgumentType::None, "Provided type does not have a formatter!");
	};

	template<typename Type>
	using FormatterEnabler = typename details::EnableIf
	<
		details::BoolConstant
		<
			details::IntegralConstant
			<
				FormatArgumentType,
				FormatOf<Type>::value()
			>::value() != FormatArgumentType::None
		>::value()
	>::Type;

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
			const details::uint32 size = 33u;
			char buffer[size] = { };
			const details::uint32 length = details::ascii::itoar(pValue COMMA buffer COMMA 10);
			pContext.appendReversed(buffer COMMA length);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, details::uint8,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA details::uint8 pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 33u;
			char buffer[size] = { };
			const details::uint32 length = details::ascii::itoar(pValue COMMA buffer COMMA 10);
			pContext.appendReversed(buffer COMMA length);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, details::int16,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA details::int16 pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 33u;
			char buffer[size] = { };
			const details::uint32 length = details::ascii::itoar(pValue COMMA buffer COMMA 10);
			pContext.appendReversed(buffer COMMA length);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, details::uint16,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA details::uint16 pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 33u;
			char buffer[size] = { };
			const details::uint32 length = details::ascii::itoar(pValue COMMA buffer COMMA 10);
			pContext.appendReversed(buffer COMMA length);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, details::int32,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA details::int32 pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 33u;
			char buffer[size] = { };
			const details::uint32 length = details::ascii::itoar(pValue COMMA buffer COMMA 10);
			pContext.appendReversed(buffer COMMA length);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, details::uint32,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA details::uint32 pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 33u;
			char buffer[size] = { };
			const details::uint32 length = details::ascii::itoar(pValue COMMA buffer COMMA 10);
			pContext.appendReversed(buffer COMMA length);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, details::int64,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA details::int64 pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 65u;
			char buffer[size] = { };
			const details::uint32 length = details::ascii::itoar(static_cast<details::int32>(pValue) COMMA buffer COMMA 10);
			pContext.appendReversed(buffer COMMA length);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, details::uint64,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA details::uint64 pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 65u;
			char buffer[size] = { };
			const details::uint32 length = details::ascii::itoar(static_cast<details::int32>(pValue) COMMA buffer COMMA 10);
			pContext.appendReversed(buffer COMMA length);
		}
	);

	__struct_INTERNAL_FORMATTER(NONE, float,
		FORMAT_INLINE FORMAT_CONSTEXPR void parse(Context& pContext) FORMAT_NOEXCEPT
		{
			FormatterHelpers::template parseIgnore<Context>(pContext);
		},
		FORMAT_INLINE FORMAT_CONSTEXPR void format(Context& pContext COMMA float pValue) FORMAT_NOEXCEPT
		{
			const details::uint32 size = 65u;
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
			const details::uint32 size = 65u;
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
			const details::uint32 size = 65u;
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

	struct ANSITextColor
	{
	public:
		static FORMAT_CONSTEXPR const char reset[] = "\u001b[0m";
		static FORMAT_CONSTEXPR const char black[] = "\u001b[30m";
		static FORMAT_CONSTEXPR const char red[] = "\u001b[31m";
		static FORMAT_CONSTEXPR const char green[] = "\u001b[32m";
		static FORMAT_CONSTEXPR const char yellow[] = "\u001b[33m";
		static FORMAT_CONSTEXPR const char blue[] = "\u001b[34m";
		static FORMAT_CONSTEXPR const char magenta[] = "\u001b[35m";
		static FORMAT_CONSTEXPR const char cyan[] = "\u001b[36m";
		static FORMAT_CONSTEXPR const char white[] = "\u001b[37m";
	};

	struct ANSIBackgroundColor
	{
	public:
		static FORMAT_CONSTEXPR const char reset[] = "\u001b[0m";
		static FORMAT_CONSTEXPR const char black[] = "\u001b[40m";
		static FORMAT_CONSTEXPR const char red[] = "\u001b[41m";
		static FORMAT_CONSTEXPR const char green[] = "\u001b[42m";
		static FORMAT_CONSTEXPR const char yellow[] = "\u001b[43m";
		static FORMAT_CONSTEXPR const char blue[] = "\u001b[44m";
		static FORMAT_CONSTEXPR const char magenta[] = "\u001b[45m";
		static FORMAT_CONSTEXPR const char cyan[] = "\u001b[46m";
		static FORMAT_CONSTEXPR const char white[] = "\u001b[47m";
	};

	struct ANSIDecorations
	{
	public:
		static FORMAT_CONSTEXPR const char reset[] = "\u001b[0m";
		static FORMAT_CONSTEXPR const char bold[] = "\u001b[1m";
		static FORMAT_CONSTEXPR const char underline[] = "\u001b[4m";
		static FORMAT_CONSTEXPR const char reversed[] = "\u001b[7m";
	};

	template<typename Reader, typename Writer>
	static FORMAT_INLINE FORMAT_CONSTEXPR void formatHandle(Reader& pReader, Writer& pWriter) FORMAT_NOEXCEPT
	{
		pWriter.append(pReader.current(), pReader.size());
	}

	template<typename Reader, typename Writer, typename Argument, typename... Arguments>
	static FORMAT_INLINE FORMAT_CONSTEXPR void formatHandle(Reader& pReader, Writer& pWriter, Argument&& pArgument, Arguments&&... pArguments) FORMAT_NOEXCEPT
	{
		pReader.setPrevious();
		for (; *(pReader.current()) != '{' && pReader.current() != pReader.end(); pReader.next());

		if (*(pReader.current()) == '{')
		{
			pWriter.append(pReader.previous(), pReader.fromPreviousToCurrent());
			using DRefArgument = typename details::RemoveVolatile<typename details::RemoveReference<Argument>::Type>::Type;
			Formatter<DRefArgument>::template parse<Reader>(pReader);
			Formatter<DRefArgument>::template format<Writer>(pWriter, pArgument);
		}

		formatHandle<Reader, Writer>(pReader, pWriter, pArguments...);
	}

	class FormatStringReader
	{
	private:
		const char* mPointer;
		const char* mCurrent;
		const char* mPrevious;
		details::uint32 mSize;

	public:
		explicit FormatStringReader(const char* pPointer, details::uint32 pSize) FORMAT_NOEXCEPT
			: mPointer(pPointer), mCurrent(pPointer), mPrevious(pPointer), mSize(pSize)
		{ }

	public:
		FORMAT_INLINE FORMAT_CONSTEXPR details::uint32 size() const FORMAT_NOEXCEPT
		{
			return this->mSize;
		}

		FORMAT_INLINE FORMAT_CONSTEXPR details::uint32 fromPreviousToCurrent() const FORMAT_NOEXCEPT
		{
			return static_cast<details::uint32>(this->mCurrent - this->mPrevious);
		}

		FORMAT_INLINE FORMAT_CONSTEXPR const char* current() const FORMAT_NOEXCEPT
		{
			return this->mCurrent;
		}

		FORMAT_INLINE FORMAT_CONSTEXPR const char* previous() const FORMAT_NOEXCEPT
		{
			return this->mPrevious;
		}

		FORMAT_INLINE FORMAT_CONSTEXPR const char* begin() const FORMAT_NOEXCEPT
		{
			return this->mPointer;
		}

		FORMAT_INLINE FORMAT_CONSTEXPR const char* end() const FORMAT_NOEXCEPT
		{
			return this->mPointer + this->mSize;
		}

		FORMAT_INLINE FORMAT_CONSTEXPR void setPrevious() FORMAT_NOEXCEPT
		{
			this->mPrevious = this->mCurrent;
		}

		FORMAT_INLINE FORMAT_CONSTEXPR void next() FORMAT_NOEXCEPT
		{
			++this->mCurrent;
		}

		FORMAT_INLINE FORMAT_CONSTEXPR void move(details::uint32 pOffset) FORMAT_NOEXCEPT
		{
			this->mCurrent += pOffset;
		}
	};

	class DynamicWriter
	{
	private:
		char* mData;
		details::uint32 mSize;
		details::uint32 mCapacity;

	public:
		explicit DynamicWriter(details::uint32 pCapacity = 4u) FORMAT_NOEXCEPT
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
			
			for (details::uint32 index = 0; index < this->mSize; index++)
				local[index] = details::move(this->mData[index]);

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
			if (this->mSize + 1u > this->mCapacity)
				reallocate(this->mCapacity + this->mCapacity / 2);
			
			this->mData[this->mSize++] = pChar;
		}

		FORMAT_INLINE FORMAT_CONSTEXPR void append(const char* const pData, details::uint32 pSize) FORMAT_NOEXCEPT
		{
			if (this->mSize + pSize > this->mCapacity)
				reallocate(pSize + this->mCapacity + this->mCapacity / 2);

			for (details::uint32 index = 0; index < pSize; index++)
				this->mData[this->mSize + index] = pData[index];

			this->mSize += pSize;
		}

		FORMAT_INLINE FORMAT_CONSTEXPR void appendReversed(const char* const pData, details::uint32 pSize) FORMAT_NOEXCEPT
		{
			if (this->mSize + pSize > this->mCapacity)
				reallocate(pSize + this->mCapacity + this->mCapacity / 2);

			for (details::uint32 index = 0; index < pSize; index++)
				this->mData[this->mSize + index] = pData[pSize - index - 1u];

			this->mSize += pSize;
		}

		FORMAT_INLINE FORMAT_CONSTEXPR char* get() FORMAT_NOEXCEPT
		{
			this->mData[this->mSize] = '\0';
			return this->mData;
		}
	};

	class StaticWriter
	{
	private:
		char* mData;
		details::uint32 mSize;
		details::uint32 mCapacity;

	public:
		explicit StaticWriter(char* pData, details::uint32 pCapacity) FORMAT_NOEXCEPT
			: mData(pData), mSize(0), mCapacity(pCapacity)
		{ }

	public:
		FORMAT_INLINE FORMAT_CONSTEXPR details::uint32 size() const FORMAT_NOEXCEPT
		{
			return this->mSize;
		}
		
		FORMAT_INLINE FORMAT_CONSTEXPR void append(char pChar) FORMAT_NOEXCEPT
		{
			if (this->mSize + 1u <= this->mCapacity + 1u)
				this->mData[this->mSize++] = pChar;
		}

		FORMAT_INLINE FORMAT_CONSTEXPR void append(const char* const pData, details::uint32 pSize) FORMAT_NOEXCEPT
		{
			if (this->mSize + pSize <= this->mCapacity + 1u)
			{
				for (details::uint32 index = 0; index < pSize; index++)
					this->mData[this->mSize + index] = pData[index];
				
				this->mSize += pSize;
			}
		}

		FORMAT_INLINE FORMAT_CONSTEXPR void appendReversed(const char* const pData, details::uint32 pSize) FORMAT_NOEXCEPT
		{
			if (this->mSize + pSize <= this->mCapacity + 1u)
			{
				for (details::uint32 index = 0; index < pSize; index++)
					this->mData[this->mSize + index] = pData[pSize - index - 1u];
				
				this->mSize += pSize;
			}
		}

		FORMAT_INLINE FORMAT_CONSTEXPR char* get() FORMAT_NOEXCEPT
		{
			this->mData[this->mSize] = '\0';
			return this->mData;
		}
	};

	template<typename... Arguments>
	static FORMAT_INLINE char* format(const char* const pPattern, Arguments&&... pArguments) FORMAT_NOEXCEPT
	{
		const details::uint32 patternLength = details::ascii::length(pPattern);
		FormatStringReader reader = FormatStringReader(pPattern, patternLength);
		DynamicWriter writer = DynamicWriter(patternLength + sizeof...(pArguments) * 2u);
		formatHandle<FormatStringReader, DynamicWriter, Arguments...>(reader, writer, details::forward<Arguments>(pArguments)...);
		return writer.get();
	}

	template<class Result, typename... Arguments>
	static FORMAT_INLINE Result sformat(const char* const pPattern, Arguments&&... pArguments) FORMAT_NOEXCEPT
	{
		const details::uint32 patternLength = details::ascii::length(pPattern);
		FormatStringReader reader = FormatStringReader(pPattern, patternLength);
		DynamicWriter writer = DynamicWriter(patternLength + sizeof...(pArguments) * 2u);
		
		formatHandle<FormatStringReader, DynamicWriter, Arguments...>(reader, writer, details::forward<Arguments>(pArguments)...);
		char* buffer = writer.get();
		Result result = Result(buffer);
		
		delete[] buffer;
		return result;
	}

	template<typename... Arguments>
	static FORMAT_INLINE details::uint32 formatTo(char pBuffer[], details::uint32 pSize, const char* const pPattern, Arguments&&... pArguments) FORMAT_NOEXCEPT
	{
		FormatStringReader reader = FormatStringReader(pPattern, details::ascii::length(pPattern));
		StaticWriter writer = StaticWriter(pBuffer, pSize);
		formatHandle<FormatStringReader, StaticWriter, Arguments...>(reader, writer, details::forward<Arguments>(pArguments)...);
		return writer.size();
	}

	template<typename Stream, typename... Arguments>
	static FORMAT_INLINE void print(Stream& pStream, const char* const pPattern, Arguments&&... pArguments) FORMAT_NOEXCEPT
	{
		char* formatted = format<Arguments...>(pPattern, details::forward<Arguments>(pArguments)...);
		pStream << formatted;
		delete[] formatted;
	}

	template<typename... Arguments>
	static FORMAT_INLINE FORMAT_CONSTEXPR void cprint(::FILE* pStream, const char* const pPattern, Arguments&&... pArguments) FORMAT_NOEXCEPT
	{
		char* formatted = format<Arguments...>(pPattern, details::forward<Arguments>(pArguments)...);
		::fwrite(formatted, sizeof(char), details::ascii::length(formatted), pStream);
		delete[] formatted;
	}
}

/**
 * Helper macros and cleanup.
 */
#undef __struct_INTERNAL_FORMAT_OF
#undef __struct_INTERNAL_FORMATTER
#undef __struct_INTERNAL_SPECIFIER_OF

#define PARSE_IGNORE(pContext) \
FormatterHelpers::template parseIgnore<Context>(pContext);

#define struct_CUSTOM_FORMAT_OF(Dependencies, Type) \
namespace cformat \
{ \
	template<Dependencies> \
	struct FormatOf<Type> \
	{ \
	public: \
		static FORMAT_CONSTEXPR const FormatArgumentType sValue = FormatArgumentType::Custom; \
		 \
		static FORMAT_INLINE FORMAT_CONSTEXPR const FormatArgumentType value() FORMAT_NOEXCEPT \
		{ return sValue; } \
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
