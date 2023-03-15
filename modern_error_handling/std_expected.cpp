#include <string>
#include <iostream>
#include <expected>

const char* ok_xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> <body> ok </body>";
const char* invalid_syntax_xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> <body> ok";
const char* invalid_char_xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> <body> 💩 </body>";
const char* unsafe_xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> <body> password=123 </body>";

enum class xml_error
{
  invalid_char,
  invalid_syntax,
  unsafe_xml
};

[[nodiscard]]
auto parse_xml(const std::string_view xml) -> std::expected<std::string, xml_error>
{
  // This check doesn't actually work
  for (const char c : xml)
    if (static_cast<unsigned char>(c) > 127)
      return std::unexpected(xml_error::invalid_char);

  if (xml.find("<body>") == std::string::npos || xml.find("</body>") == std::string::npos)
    return std::unexpected(xml_error::invalid_syntax);

  if (xml.find("password") != std::string::npos)
    return std::unexpected(xml_error::unsafe_xml);

  return std::string("ok");
}

auto main(void) -> int
{
  const auto response = parse_xml(ok_xml);

  if (response.has_value())
  {
    std::cout << response.value() << "\n";
  }
  else if (response.error() == xml_error::invalid_syntax)
  {
    std::cout << "ERROR: xml_error::invalid_syntax\n";
    return 1;
  }
  else if (response.error() == xml_error::invalid_char)
  {
    std::cout << "ERROR: xml_error::invalid_char\n";
    return 1;
  }
  else if (response.error() == xml_error::unsafe_xml)
  {
    std::cout << "ERROR: xml_error::unsafe_xml\n";
    return 1;
  }
}