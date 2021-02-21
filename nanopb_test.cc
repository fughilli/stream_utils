#include <iostream>

#include "base64_stream.h"
#include "pb_stream.h"
#include "stream.h"
#include "stream_utils/control_message.nanopb.h"

int main() {
  util::OstreamAdapter oa(&std::cout);
  util::Base64EncodeStream b64encoder;
  b64encoder.RegisterDownstream(&oa);

  Control control = Control_init_default;
  control.has_value = 1;
  control.value = 123;

  pb_ostream_t pb_stream = WrapStream(&b64encoder);
  pb_encode(&pb_stream, Control_fields, &control);
  b64encoder.Flush();
  std::cout << std::endl;
  return 0;
}
