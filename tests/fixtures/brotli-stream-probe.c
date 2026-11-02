/* Bounded CVE-2026-111497 malformed-stream regression and valid-stream check. */
#include <brotli/decode.h>
#include <brotli/encode.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  char hex[256];
  uint8_t malformed[128];
  size_t malformed_size = 0;
  uint8_t output[256];
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out = sizeof(output);
  uint8_t *next_out = output;
  size_t total_out = 0;
  BrotliDecoderState *state;
  BrotliDecoderResult result;
  int error_code;
  const uint8_t valid_input[] = "GetPatched Brotli compatibility probe";
  uint8_t compressed[128];
  size_t compressed_size = sizeof(compressed);
  uint8_t decoded[128];
  size_t decoded_size = sizeof(decoded);
  int compatible;

  if (argc != 2) {
    fprintf(stderr, "usage: %s fixture.hex\n", argv[0]);
    return 2;
  }
  FILE *file = fopen(argv[1], "r");
  if (file == NULL || fgets(hex, sizeof(hex), file) == NULL) {
    if (file != NULL) fclose(file);
    fputs("fixture_read_failed\n", stderr);
    return 2;
  }
  fclose(file);
  size_t hex_len = strcspn(hex, "\r\n \t");
  if (hex_len == 0 || (hex_len % 2) != 0 || hex_len / 2 > sizeof(malformed)) {
    fputs("fixture_invalid\n", stderr);
    return 2;
  }
  malformed_size = hex_len / 2;
  for (size_t i = 0; i < malformed_size; i++) {
    unsigned int value;
    if (sscanf(hex + 2 * i, "%2x", &value) != 1) {
      fputs("fixture_invalid_hex\n", stderr);
      return 2;
    }
    malformed[i] = (uint8_t)value;
  }

  state = BrotliDecoderCreateInstance(NULL, NULL, NULL);
  if (state == NULL) return 2;
  available_in = malformed_size;
  next_in = malformed;
  result = BrotliDecoderDecompressStream(state, &available_in, &next_in,
                                         &available_out, &next_out, &total_out);
  error_code = BrotliDecoderGetErrorCode(state);
  printf("malformed_result=%d error=%d format_error=%d input_remaining=%zu output=%zu\n",
         (int)result, error_code,
         (int)BROTLI_DECODER_ERROR_FORMAT_BLOCK_SWITCH, available_in, total_out);
  BrotliDecoderDestroyInstance(state);

  compatible = BrotliEncoderCompress(BROTLI_DEFAULT_QUALITY,
                                     BROTLI_DEFAULT_WINDOW,
                                     BROTLI_MODE_GENERIC,
                                     sizeof(valid_input) - 1, valid_input,
                                     &compressed_size, compressed) &&
               BrotliDecoderDecompress(compressed_size, compressed,
                                       &decoded_size, decoded) &&
               decoded_size == sizeof(valid_input) - 1 &&
               memcmp(decoded, valid_input, decoded_size) == 0;
  printf("compatible=%s\n", compatible ? "yes" : "no");
  return compatible ? 0 : 1;
}
