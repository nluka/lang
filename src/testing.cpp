#include "test.hpp"
#include "lexer.hpp"

using std::vector;
using lexer::Token;

int main(void) {
  std::ofstream out("testing.out");

  test::set_indentation("  ");
  test::set_verbose_mode(false);
  test::set_ofstream(&out);

  {
    SETUP_SUITE_USING(lexer::tokenize)

    auto const case_ = [&s](
      char const *const text,
      vector<Token> const &expected
    ) {
      vector<Token> const result = tokenize(text);
      s.assert(
        text,
        result.size() == expected.size() &&
        [&]() {
          for (size_t i = 0; i < result.size(); ++i) {
            if (result[i] != expected[i]) {
              return false;
            }
          }
          return true;
        }()
      );
    };

    {
      vector<Token> const expected {
        { Token::Kind::KEYWORD, 2, 0 },
        { Token::Kind::IDENTIFIER, 4, 3 },
        { Token::Kind::PUNCT, 1, 7 },
        { Token::Kind::PUNCT, 1, 8 },
        { Token::Kind::PUNCT, 1, 9 },
        { Token::Kind::KEYWORD, 3, 11 },
        { Token::Kind::PUNCT, 1, 15 },
        { Token::Kind::KEYWORD, 3, 17 },
        { Token::Kind::NUMBER, 1, 21 },
        { Token::Kind::PUNCT, 1, 23 },
        { Token::Kind::NUMBER, 2, 25 },
        { Token::Kind::PUNCT, 1, 27 },
        { Token::Kind::PUNCT, 1, 29 },
        { Token::Kind::END, 0, 30 },
      };
      case_("fn main(): i32 { ret 1 + 23; }", expected);
    }

  } // lexer::tokenize

  test::evaluate_suites();

  return static_cast<int>(test::assertions_failed());
}
