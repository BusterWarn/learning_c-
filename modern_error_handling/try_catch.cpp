#include <string>
#include <iostream>
#include <stdexcept>

// #define CRASH
#ifdef CRASH
#include <vector>
#endif

// #define UNDEFINED_BEHAVIOUR
#ifdef UNDEFINED_BEHAVIOUR
#include <vector>
#endif

// #define UNDEFINED_BEHAVIOUR_CRASH
#ifdef UNDEFINED_BEHAVIOUR_CRASH
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
  // This check doesn't actually work
  for (const char c : xml)
    if (static_cast<unsigned char>(c) > 127)
      throw std::invalid_argument("Invalid XML");

  if (xml.find("<body>") == std::string::npos || xml.find("</body>") == std::string::npos)
    throw std::invalid_argument("Invalid XML");

  if (xml.find("password") != std::string::npos)
    throw unsafe_xml_exception("That is really not a safe password");

#ifdef CRASH
  std::vector<int> vec = {1, 2, 3};
  const auto value = vec.at(4);
#endif

#ifdef UNDEFINED_BEHAVIOUR
  std::vector<int> vec = {1, 2, 3};
  const auto value = vec[99999];
#endif

#ifdef UNDEFINED_BEHAVIOUR_CRASH
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
    std::cout << "parsed xml: " << parse_xml(ok_xml) << "\n";
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