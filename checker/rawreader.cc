
#include <DataFormatsTRD/Digit.h>
#include <TRDReconstruction/DigitsParser.h>
#include <TRDReconstruction/CruRawReader.h>
#include <boost/iostreams/device/mapped_file.hpp>

// #include <fmt/fmt.h>
#include <fmt/color.h>

#include <iostream>

struct {
  fmt::text_style dh   = fg(fmt::color::black) | bg(fmt::color::light_green);
  fmt::text_style addr = fg(fmt::color::gray);
} sty;


class dword_dump
{
public:
  dword_dump() : mBaseAddr(NULL), mAddrFmt("{:06X}: ") {};
  ~dword_dump() {};

  void SetBaseAddress(const char* addr) { mBaseAddr = const_cast<char*>(addr); }

  std::string operator()(const void* data, int ndword=1)
  {
    std::string out = "";
    if (mBaseAddr) {
      out = fmt::format(sty.addr, mAddrFmt, reinterpret_cast<const char*>(data)-mBaseAddr);
    }
    for (int i=0; i<ndword; i++) {
      out += fmt::format(" {:08X}", reinterpret_cast<const uint32_t*>(data)[i]);
    }
    return out;
  }

protected:
  char* mBaseAddr;
  std::string mAddrFmt;
} dw;


// using namespace std;


template <> struct fmt::formatter<o2::header::DataHeader> {
  // Presentation format: 'f' - fixed, 'e' - exponential.
  // char presentation = 'f';

  // Parses format specifications of the form ['f' | 'e'].
  constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
    // [ctx.begin(), ctx.end()) is a character range that contains a part of
    // the format string starting from the format specifications to be parsed,
    // e.g. in
    //
    //   fmt::format("{:f} - point of interest", point{1, 2});
    //
    // the range will contain "f} - point of interest". The formatter should
    // parse specifiers until '}' or the end of the range. In this example
    // the formatter should parse the 'f' specifier and return an iterator
    // pointing to '}'.

    // Parse the presentation format and store it in the formatter:
    auto it = ctx.begin(), end = ctx.end();
    // if (it != end && (*it == 'f' || *it == 'e')) presentation = *it++;

    // Check if reached the end of the range:
    if (it != end && *it != '}')
      throw format_error("invalid format");

    // Return an iterator past the end of the parsed range:
    return it;
  }

  // Formats the point p using the parsed format specification (presentation)
  // stored in this formatter.
  template <typename FormatContext>
  auto format(const o2::header::DataHeader& dh, FormatContext& ctx) -> decltype(ctx.out()) {
    // ctx.out() is an output iterator to write to.
    return format_to(
        ctx.out(),
        "DataHeader \"{}\" payload: {} bytes",
        reinterpret_cast<const char*>(&dh.dataOrigin),
        dh.payloadSize);
  }
};



char* mRefAddr;
size_t addr(const void* ptr)
{ return reinterpret_cast<const char*>(ptr) - mRefAddr; }

// int main(int argc, char** argv)
int main()
{

  fair::Logger::SetConsoleSeverity("trace");

  boost::iostreams::mapped_file_source rawfile("tfdata/2021-07-28_00000001.tf");
  mRefAddr = const_cast<char*>(rawfile.data());

  size_t offset = 0;
  
  o2::trd::CruRawReader rdr;
  rdr.configure(true, false, 0, true, true, true);

  while (true) {

    auto header = reinterpret_cast<const uint32_t*>(rawfile.data() + offset);
    auto dh = reinterpret_cast<const o2::header::DataHeader*>(header);

    auto payload = header + dh->headerSize/4;

    LOGP(info, "{:06X}: === {} ===", addr(dh), *dh);

    if (dh->dataOrigin == o2::header::gDataOriginTRD) {
      for (size_t i=0; i < dh->payloadSize/32; i++) {
        LOG(debug) << dw(payload + 8*i, 8);
      }

      rdr.setDataBuffer(
        rawfile.data() + offset + sizeof(o2::header::DataHeader),
        rawfile.data()
      );
      rdr.setDataBufferSize(dh->payloadSize);

      rdr.run();
    }

    offset += sizeof(o2::header::DataHeader) + dh->payloadSize;
  }

}
