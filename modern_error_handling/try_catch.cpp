#include <string>
#include <iostream>
#include <cstdint>
#include <stdexcept>

// #define cause_crash
#ifdef cause_crash
#include <memory>
#endif

const char* ok_xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> <body> ok </body>";
const char* invalid_syntax_xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> <body> ok";
const char* invalid_char_xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> <body> 💩 </body>";
const char* unsafe_xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> <body> password=123 </body>";

class unsafe_xml_exception : public std::exception
{
  const char* what_msg;
public:
  unsafe_xml_exception(const char* msg) : what_msg(msg) {}

  const char* what() const throw() override
  {
    return what_msg;
  }
};

[[nodiscard]]
std::string parse_xml(const std::string_view xml)
{
  // This check doesen't actually work
  for (const char c : xml)
    if (static_cast<unsigned char>(c) > 127)
      throw std::invalid_argument("Invalid XML");

  if (xml.find("<body>") == std::string::npos || xml.find("</body>") == std::string::npos)
    throw std::invalid_argument("Invalid XML");

  if (xml.find("password") != std::string::npos)
    throw unsafe_xml_exception("That is really not a safe password");

#ifdef cause_crash
  int* value = new int{42};
  std::shared_ptr sp1 = std::shared_ptr<int>(value);
  std::shared_ptr sp2 = std::shared_ptr<int>(value);
#endif
  
  return "ok";
}

auto main(void) -> int
{
  try
  {
    std::cout << "parsed xml: " << parse_xml(unsafe_xml) << "\n";
  }
  catch (const unsafe_xml_exception& e)
  {
    std::cout << "ERROR: unsafe_xml_exception " << e.what() << '\n';
    return 1;
  }
  catch (const std::invalid_argument& e)
  {
    std::cout << "ERROR: invalid_argument " << e.what() << '\n';
    return 1;
  }
  catch (const std::runtime_error& e)
  {
    std::cout << "ERROR: runtime_error " << e.what() << '\n';
    return 1;
  }
  catch (const std::exception& e)
  {
    std::cout << "ERROR: exception " << e.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cout << "ERROR: ... \n";
    return 1;
  }
}