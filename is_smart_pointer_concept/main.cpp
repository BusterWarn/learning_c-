#include <memory>
#include <type_traits>

template<typename Pointer>
concept is_smart_pointer_1 = requires(Pointer pointer)
{
  typename Pointer::element_type;
  { pointer.operator->() } -> std::same_as<typename Pointer::element_type*>;
};

static_assert(is_smart_pointer_1<std::unique_ptr<int>>);
static_assert(is_smart_pointer_1<std::shared_ptr<int>>);
static_assert(!is_smart_pointer_1<std::weak_ptr<int>>);
static_assert(!is_smart_pointer_1<int>);

// Define a template structure with a static constexpr bool value.
template <typename Pointer>
struct _is_smart_ptr : std::false_type {};

// Specialize the template structure for std::unique_ptr and std::shared_ptr.
template <typename Pointer>
struct _is_smart_ptr<std::unique_ptr<Pointer>> : std::true_type {};

template <typename Pointer>
struct _is_smart_ptr<std::shared_ptr<Pointer>> : std::true_type {};

// Define the concept using the helper structure.
template <typename Pointer>
concept is_smart_pointer_2 = _is_smart_ptr<Pointer>::value;


static_assert(is_smart_pointer_2<std::unique_ptr<int>>);
static_assert(is_smart_pointer_2<std::shared_ptr<int>>);
static_assert(!is_smart_pointer_2<std::weak_ptr<int>>);
static_assert(!is_smart_pointer_2<int>);

int main() {}