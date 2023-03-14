#include <string>
#include <iostream>
#include <cstdint>

#define OK_XML 0
#define INVALID_SYNTAX_XML 0
#define INVALID_CHAR_XML 1
#define UNSAFE_XML 2

const char* ok_xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> <body> ok </body>";
const char* invalid_syntax_xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> <body> ok";
const char* invalid_char_xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> <body> 💩 </body>";
const char* unsafe_xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> <body> password=123 </body>";

[[nodiscard]]
std::uint32_t parse_xml(const std::string_view xml,
                        std::string& out_parsed_data)
{
  // This check doesen't actually work
  for (const char c : xml)
    if (static_cast<unsigned char>(c) > 127)
      return INVALID_CHAR_XML;

  if (xml.find("<body>") == std::string::npos || xml.find("</body>") == std::string::npos)
    return INVALID_SYNTAX_XML;

  if (xml.find("password") != std::string::npos)
    return UNSAFE_XML;

  out_parsed_data = "ok";
  return OK_XML;
}

auto main(void) -> int
{
  std::string parsed_xml;
  const auto response = parse_xml(parsed_xml, parsed_xml);

  if (response == OK_XML)
  {
    std::cout << "parsed xml: " << parsed_xml << "\n";
  }
  else if (response == INVALID_SYNTAX_XML)
  {
    std::cout << "ERROR: INVALID_SYNTAX_XML\n";
    return 1;
  }
  else if (response == INVALID_CHAR_XML)
  {
    std::cout << "ERROR: INVALID_CHAR_XML\n";
    return 1;
  }
  else if (response == UNSAFE_XML)
  {
    std::cout << "ERROR: UNSAFE_XML\n";
    return 1;
  }
}