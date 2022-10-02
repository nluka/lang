#ifndef LEXER_HPP
#define LEXER_HPP

#include <cinttypes>
#include <vector>

namespace lexer {

struct Token {
  enum class Kind : uint8_t {
    END,
    UNKNOWN,
    TOO_LONG,

    KEYWORD,
    IDENTIFIER,
    NUMBER,
    PUNCT,
  };

  Kind m_kind;
  uint16_t m_len;
  uint32_t m_pos;

  bool operator==(Token const &) const noexcept;
  bool operator!=(Token const &) const noexcept;
};

std::vector<Token> tokenize(char const *text);

} // namespace lexer

#endif // LEXER_HPP
