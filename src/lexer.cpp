#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "lexer.hpp"

using std::vector;
using lexer::Token;

bool Token::operator==(Token const &other) const noexcept {
  return m_kind == other.m_kind && m_pos == other.m_pos && m_len == other.m_len;
}
bool Token::operator!=(Token const &other) const noexcept {
  return !(*this == other);
}

static char const *s_keywords[] {
  "fn", "ret", "let", "const",
  "i8", "i16", "i32", "i64",
  // "u8", "u16", "u32", "u64",
};

bool is_alpha(char const ch) {
  return
    (ch >= 'A' && ch <= 'Z') ||
    (ch >= 'a' && ch <= 'z');
}
bool is_digit(char const ch) {
  return (ch >= '0' && ch <= '9');
}
bool is_punct(char const ch) {
  char const punct[] = "(){}[]:;+-/*";
  return std::strchr(punct, ch);
}

struct Tokenizer {
  char const *const m_text;
  uint32_t m_pos = 0;

  Token next();
};

Token Tokenizer::next() {
  if (m_text[m_pos] == '\0') {
    return { Token::Kind::END, 0, m_pos };
  }

  // skip whitespace
  while (std::strchr(" \t\n", m_text[m_pos])) {
    ++m_pos;
  }

  uint32_t const startPos = m_pos;
  char const firstCh = m_text[m_pos];

  if (is_alpha(firstCh)) {
    do {
      ++m_pos;
    } while (
      is_alpha(m_text[m_pos]) ||
      is_digit(m_text[m_pos]) ||
      m_text[m_pos] == '_'
    );

    uint32_t const len = m_pos - startPos;
    if (len > UINT16_MAX) {
      return { Token::Kind::TOO_LONG, 0, startPos };
    }

    Token::Kind const kind = [=]() {
      char val[UINT16_MAX + 1];
      std::memcpy(val, m_text + startPos, len);
      val[len] = '\0';

      for (auto const keyword : s_keywords) {
        if (std::strcmp(val, keyword) == 0) {
          return Token::Kind::KEYWORD;
        }
      }

      return Token::Kind::IDENTIFIER;
    }();

    return { kind, static_cast<uint16_t>(len), startPos };
  }

  if (is_digit(firstCh)) {
    do {
      ++m_pos;
    } while (is_digit(m_text[m_pos]));

    uint32_t const len = m_pos - startPos;
    if (len > UINT16_MAX) {
      return { Token::Kind::TOO_LONG, 0, startPos };
    }

    return { Token::Kind::NUMBER, static_cast<uint16_t>(len), startPos };
  }

  if (is_punct(firstCh)) {
    ++m_pos;
    return { Token::Kind::PUNCT, 1, startPos };
  }

  return { Token::Kind::UNKNOWN, 0, 0 };
}

vector<Token> lexer::tokenize(char const *const text) {
  vector <Token> tokens{};

  Tokenizer tokenizer{ text, 0 };
  Token tok{};
  do {
    tok = tokenizer.next();
    tokens.push_back(tok);
  } while (tok.m_kind != Token::Kind::END);

  return tokens;
}
