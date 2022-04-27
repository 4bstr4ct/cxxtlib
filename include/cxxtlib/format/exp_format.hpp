/*

template <typename Context, typename... Args>
class format_arg_store
#if FMT_GCC_VERSION && FMT_GCC_VERSION < 409
    // Workaround a GCC template argument substitution bug.
    : public basic_format_args<Context>
#endif
{
 private:
  static const size_t num_args = sizeof...(Args);
  static const size_t num_named_args = detail::count_named_args<Args...>();
  static const bool is_packed = num_args <= detail::max_packed_args;

  using value_type = conditional_t<is_packed, detail::value<Context>,
                                   basic_format_arg<Context>>;

  detail::arg_data<value_type, typename Context::char_type, num_args,
                   num_named_args>
      data_;

  friend class basic_format_args<Context>;

  static constexpr unsigned long long desc =
      (is_packed ? detail::encode_types<Context, Args...>()
                 : detail::is_unpacked_bit | num_args) |
      (num_named_args != 0
           ? static_cast<unsigned long long>(detail::has_named_args_bit)
           : 0);

 public:
  template <typename... T>
  FMT_CONSTEXPR FMT_INLINE format_arg_store(T&&... args)
      :
#if FMT_GCC_VERSION && FMT_GCC_VERSION < 409
        basic_format_args<Context>(*this),
#endif
        data_{detail::make_arg<
            is_packed, Context,
            detail::mapped_type_constant<remove_cvref_t<T>, Context>::value>(
            std::forward<T>(args))...} {
    detail::init_named_args(data_.named_args(), 0, 0, args...);
  }
};

*/