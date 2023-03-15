#include <string>
#include <iostream>
#include <expected>
#include <variant>
#include <type_traits>

const char* ok_xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> <body> ok </body>";
const char* invalid_syntax_xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> <body> ok";
const char* invalid_char_xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> <body> 💩 </body>";
const char* unsafe_xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> <body> password=123 </body>";

// ctrl c + ctrl v https://en.cppreference.com/w/cpp/utility/variant/visit
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

enum class xml_error
{
  invalid_char,
  invalid_syntax
};

struct unsafe_xml_error
{
  unsafe_xml_error(const char* msg) : error(msg) {}

  [[nodiscard]]
  auto what() const -> const char*
  {
    return error;
  }
private:
  const char* error;
};

[[nodiscard]]
auto is_xml_safe(const std::string_view xml) -> std::expected<std::string, unsafe_xml_error>
{
  if (xml.find("password") != std::string::npos)
    return std::unexpected(unsafe_xml_error("That is really not a safe password"));
  
  return std::string("xml is safe");
}

[[nodiscard]]
auto parse_xml(const std::string_view xml) -> std::expected<std::string, std::variant<xml_error, unsafe_xml_error>>
{
  // This check doesn't actually work
  for (const char c : xml)
    if (static_cast<unsigned char>(c) > 127)
      return std::unexpected(xml_error::invalid_char);

  if (xml.find("<body>") == std::string::npos || xml.find("</body>") == std::string::npos)
    return std::unexpected(xml_error::invalid_syntax);

  if (const auto response = is_xml_safe(xml); !response.has_value())
    return std::unexpected(response.error());

  return std::string("ok");
}

auto main(void) -> int
{
  const auto response = parse_xml(ok_xml);

  if (response.has_value())
  {
    std::cout << response.value() << "\n";
  }
  else
  {
    std::visit(overloaded {
      [](xml_error e)
      {
        switch (e)
        {
          case xml_error::invalid_char: { std::cout << "ERROR invalid_char\n"; break; }
          case xml_error::invalid_syntax: { std::cout << "ERROR invalid_syntax\n"; break; }
        }
      },
      [](unsafe_xml_error e)
      {
        std::cout << "ERROR unsafe_xml_error " << e.what() << '\n';
      },
      [](auto& [[maybe_unused]] e)
      {
        std::cout << "ERROR ...\n";
      }
    }, response.error());
  }
}