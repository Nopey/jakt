#include "lexer.h"
namespace Jakt {
namespace lexer {
ErrorOr<DeprecatedString> lexer::Lexer::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("Lexer("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("index: {}, ", index));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("input: {}, ", input));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("compiler: {}, ", *compiler));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("comment_contents: {}, ", comment_contents));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("illegal_cpp_keywords: {}", illegal_cpp_keywords));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<JaktInternal::Optional<DeprecatedString>> lexer::Lexer::consume_comment_contents() {
{
if ((!(((((*this).comment_contents)).has_value())))){
return JaktInternal::OptionalNone();
}
JaktInternal::DynamicArray<u8> const contents = (((*this).comment_contents).value());
(((*this).comment_contents) = JaktInternal::OptionalNone());
DeprecatedStringBuilder builder = DeprecatedStringBuilder::create();
{
JaktInternal::ArrayIterator<u8> _magic = ((contents).iterator());
for (;;){
JaktInternal::Optional<u8> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
u8 c = (_magic_value.value());
{
TRY((((builder).append(c))));
}

}
}

return TRY((((builder).to_string())));
}
}

ErrorOr<lexer::Token> lexer::Lexer::lex_quoted_string(u8 const delimiter) {
{
size_t const start = ((*this).index);
(++(((*this).index)));
if (((*this).eof())){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("unexpected eof"sv)),((*this).span(start,start))))));
return lexer::Token::Garbage(JaktInternal::OptionalNone(),((*this).span(start,start)));
}
bool escaped = false;
while (((!(((*this).eof()))) && (escaped || ((((*this).peek())) != (delimiter))))){
if ((((((*this).peek())) == (static_cast<u8>(u8'\r'))) || ((((*this).peek())) == (static_cast<u8>(u8'\n'))))){
(++(((*this).index)));
continue;
}
if (((!(escaped)) && ((((*this).peek())) == (static_cast<u8>(u8'\\'))))){
(escaped = true);
}
else {
(escaped = false);
}

(++(((*this).index)));
}
DeprecatedString const str = TRY((((*this).substring(JaktInternal::checked_add(start,static_cast<size_t>(1ULL)),((*this).index)))));
((((*this).index)++));
size_t const end = ((*this).index);
if (((delimiter) == (static_cast<u8>(u8'\'')))){
return lexer::Token::SingleQuotedString(str,JaktInternal::OptionalNone(),((*this).span(start,end)));
}
return lexer::Token::QuotedString(str,((*this).span(start,end)));
}
}

ErrorOr<JaktInternal::Optional<lexer::Token>> lexer::Lexer::next() {
{
for (;;){
if (((((*this).index)) == (((((*this).input)).size())))){
(++(((*this).index)));
return lexer::Token::Eof(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)))));
}
if (((*this).eof())){
return JaktInternal::OptionalNone();
}
u8 const ch = ((*this).peek());
if (utility::is_whitespace(ch)){
((((*this).index)++));
}
else {
break;
}

}
size_t const start = ((*this).index);
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<lexer::Token>,ErrorOr<JaktInternal::Optional<lexer::Token>>>{
auto __jakt_enum_value = (((((*this).input))[((*this).index)]));
if (__jakt_enum_value == static_cast<u8>(u8'(')) {
return JaktInternal::ExplicitValue(lexer::Token::LParen(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8')')) {
return JaktInternal::ExplicitValue(lexer::Token::RParen(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'[')) {
return JaktInternal::ExplicitValue(lexer::Token::LSquare(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8']')) {
return JaktInternal::ExplicitValue(lexer::Token::RSquare(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'{')) {
return JaktInternal::ExplicitValue(lexer::Token::LCurly(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'}')) {
return JaktInternal::ExplicitValue(lexer::Token::RCurly(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'<')) {
return JaktInternal::ExplicitValue(((*this).lex_less_than()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'>')) {
return JaktInternal::ExplicitValue(((*this).lex_greater_than()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'.')) {
return JaktInternal::ExplicitValue(((*this).lex_dot()));
}
else if (__jakt_enum_value == static_cast<u8>(u8',')) {
return JaktInternal::ExplicitValue(lexer::Token::Comma(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'~')) {
return JaktInternal::ExplicitValue(lexer::Token::Tilde(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8';')) {
return JaktInternal::ExplicitValue(lexer::Token::Semicolon(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8':')) {
return JaktInternal::ExplicitValue(((*this).lex_colon()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'?')) {
return JaktInternal::ExplicitValue(((*this).lex_question_mark()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'+')) {
return JaktInternal::ExplicitValue(((*this).lex_plus()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'-')) {
return JaktInternal::ExplicitValue(((*this).lex_minus()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'*')) {
return JaktInternal::ExplicitValue(((*this).lex_asterisk()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'/')) {
return JaktInternal::ExplicitValue(TRY((((*this).lex_forward_slash()))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'^')) {
return JaktInternal::ExplicitValue(((*this).lex_caret()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'|')) {
return JaktInternal::ExplicitValue(((*this).lex_pipe()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'%')) {
return JaktInternal::ExplicitValue(((*this).lex_percent_sign()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'!')) {
return JaktInternal::ExplicitValue(((*this).lex_exclamation_point()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'&')) {
return JaktInternal::ExplicitValue(((*this).lex_ampersand()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'$')) {
return JaktInternal::ExplicitValue(lexer::Token::Dollar(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue(((*this).lex_equals()));
}
else if (__jakt_enum_value == static_cast<u8>(u8'\n')) {
return JaktInternal::ExplicitValue(lexer::Token::Eol(TRY((((*this).consume_comment_contents()))),((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'\'')) {
return JaktInternal::ExplicitValue(TRY((((*this).lex_quoted_string(static_cast<u8>(u8'\''))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'\"')) {
return JaktInternal::ExplicitValue(TRY((((*this).lex_quoted_string(static_cast<u8>(u8'"'))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'b')) {
return JaktInternal::ExplicitValue(TRY((((*this).lex_character_constant_or_name()))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'c')) {
return JaktInternal::ExplicitValue(TRY((((*this).lex_character_constant_or_name()))));
}
else {
return JaktInternal::ExplicitValue(TRY((((*this).lex_number_or_name()))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<lexer::Token> lexer::Lexer::lex_character_constant_or_name() {
{
if (((((*this).peek_ahead(static_cast<size_t>(1ULL)))) != (static_cast<u8>(u8'\'')))){
return TRY((((*this).lex_number_or_name())));
}
JaktInternal::Optional<DeprecatedString> const prefix = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<DeprecatedString>,ErrorOr<lexer::Token>>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'b')) {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("b"sv)));
}
else if (__jakt_enum_value == static_cast<u8>(u8'c')) {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("c"sv)));
}
else {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if (((prefix).has_value())){
((((*this).index)) += (static_cast<size_t>(1ULL)));
}
size_t const start = ((*this).index);
((((*this).index)++));
bool escaped = false;
while (((!(((*this).eof()))) && (escaped || ((((*this).peek())) != (static_cast<u8>(u8'\'')))))){
if ((escaped && [](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(JaktInternal::checked_sub(((*this).index),start),static_cast<size_t>(3ULL)))){
break;
}
else if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(JaktInternal::checked_sub(((*this).index),start),static_cast<size_t>(2ULL))){
break;
}
if (((!(escaped)) && ((((*this).peek())) == (static_cast<u8>(u8'\\'))))){
(escaped = true);
}
((((*this).index)++));
}
if ((((*this).eof()) || ((((*this).peek())) != (static_cast<u8>(u8'\''))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Expected single quote"sv)),((*this).span(start,start))))));
}
((((*this).index)) += (static_cast<size_t>(1ULL)));
DeprecatedStringBuilder builder = DeprecatedStringBuilder::create();
TRY((((builder).append(((((*this).input))[JaktInternal::checked_add(start,static_cast<size_t>(1ULL))])))));
if (escaped){
TRY((((builder).append(((((*this).input))[JaktInternal::checked_add(start,static_cast<size_t>(2ULL))])))));
}
DeprecatedString const quote = TRY((((builder).to_string())));
size_t const end = ((*this).index);
return lexer::Token::SingleQuotedString(quote,prefix,((*this).span(start,end)));
}
}

lexer::Token lexer::Lexer::lex_dot() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'.')) {
return JaktInternal::ExplicitValue(lexer::Token::DotDot(((*this).span(start,(++(((*this).index)))))));
}
else {
return JaktInternal::ExplicitValue(lexer::Token::Dot(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

lexer::Token lexer::Lexer::lex_question_mark() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'?')) {
return JaktInternal::ExplicitValue(({ Optional<lexer::Token> __jakt_var_4; {
((((*this).index)++));
__jakt_var_4 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue(lexer::Token::QuestionMarkQuestionMarkEqual(((*this).span(start,(++(((*this).index)))))));
}
else {
return JaktInternal::ExplicitValue(lexer::Token::QuestionMarkQuestionMark(((*this).span(start,((*this).index)))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_0;

}
__jakt_label_0:; __jakt_var_4.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(lexer::Token::QuestionMark(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<lexer::Token> lexer::Lexer::lex_forward_slash() {
{
size_t const start = ((((*this).index)++));
if (((((*this).peek())) == (static_cast<u8>(u8'=')))){
return lexer::Token::ForwardSlashEqual(((*this).span(start,(++(((*this).index))))));
}
if (((((*this).peek())) != (static_cast<u8>(u8'/')))){
return lexer::Token::ForwardSlash(((*this).span(start,((*this).index))));
}
if (((((*this).comment_contents)).has_value())){
((((*this).index)--));
return lexer::Token::Eol(TRY((((*this).consume_comment_contents()))),((*this).span(start,((*this).index))));
}
((((*this).index)++));
size_t const comment_start_index = ((*this).index);
while ((!(((*this).eof())))){
u8 const c = ((*this).peek());
((((*this).index)++));
if (((c) == (static_cast<u8>(u8'\n')))){
((((*this).index)--));
break;
}
}
(((*this).comment_contents) = TRY((((((((*this).input))[(JaktInternal::Range<size_t>{static_cast<size_t>(comment_start_index),static_cast<size_t>(((*this).index))})])).to_array()))));
return TRY((((*this).next()))).value_or_lazy_evaluated([&] { return lexer::Token::Eof(((*this).span(((*this).index),((*this).index)))); });
}
}

u8 lexer::Lexer::peek_behind(size_t const steps) const {
{
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(((*this).index),steps)){
return static_cast<u8>(0);
}
return ((((*this).input))[JaktInternal::checked_sub(((*this).index),steps)]);
}
}

u8 lexer::Lexer::peek_ahead(size_t const steps) const {
{
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(JaktInternal::checked_add(((*this).index),steps),((((*this).input)).size()))){
return static_cast<u8>(0);
}
return ((((*this).input))[JaktInternal::checked_add(((*this).index),steps)]);
}
}

lexer::Token lexer::Lexer::lex_asterisk() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue(lexer::Token::AsteriskEqual(((*this).span(start,(++(((*this).index)))))));
}
else {
return JaktInternal::ExplicitValue(lexer::Token::Asterisk(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

lexer::Token lexer::Lexer::lex_minus() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue(lexer::Token::MinusEqual(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'-')) {
return JaktInternal::ExplicitValue(lexer::Token::MinusMinus(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'>')) {
return JaktInternal::ExplicitValue(lexer::Token::Arrow(((*this).span(start,(++(((*this).index)))))));
}
else {
return JaktInternal::ExplicitValue(lexer::Token::Minus(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

u8 lexer::Lexer::peek() const {
{
if (((*this).eof())){
return static_cast<u8>(0);
}
return ((((*this).input))[((*this).index)]);
}
}

lexer::Token lexer::Lexer::lex_percent_sign() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue(lexer::Token::PercentSignEqual(((*this).span(start,(++(((*this).index)))))));
}
else {
return JaktInternal::ExplicitValue(lexer::Token::PercentSign(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<lexer::Token> lexer::Lexer::lex_number_or_name() {
{
size_t const start = ((*this).index);
if (((*this).eof())){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("unexpected eof"sv)),((*this).span(start,start))))));
return lexer::Token::Garbage(JaktInternal::OptionalNone(),((*this).span(start,start)));
}
if (utility::is_ascii_digit(((*this).peek()))){
return TRY((((*this).lex_number())));
}
else if ((utility::is_ascii_alpha(((*this).peek())) || ((((*this).peek())) == (static_cast<u8>(u8'_'))))){
DeprecatedStringBuilder string_builder = DeprecatedStringBuilder::create();
while ((utility::is_ascii_alphanumeric(((*this).peek())) || ((((*this).peek())) == (static_cast<u8>(u8'_'))))){
u8 const value = ((((*this).input))[((*this).index)]);
(++(((*this).index)));
TRY((((string_builder).append(value))));
}
size_t const end = ((*this).index);
utility::Span const span = ((*this).span(start,end));
DeprecatedString const string = TRY((((string_builder).to_string())));
if (([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(JaktInternal::checked_sub(end,start),static_cast<size_t>(6ULL)) && ((((string).substring(static_cast<size_t>(0ULL),static_cast<size_t>(6ULL)))) == (TRY(DeprecatedString::from_utf8("__jakt"sv)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("reserved identifier name"sv)),span))));
}
if (((((*this).illegal_cpp_keywords)).contains(string))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("C++ keywords are not allowed to be used as identifiers"sv)),span))));
}
return TRY((lexer::Token::from_keyword_or_identifier(string,span)));
}
u8 const unknown_char = ((((*this).input))[((*this).index)]);
size_t const end = (++(((*this).index)));
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("unknown character: {:c}"sv)),unknown_char))),((*this).span(start,end))))));
return lexer::Token::Garbage(TRY((__jakt_format((StringView::from_string_literal("{:c}"sv)),unknown_char))),((*this).span(start,end)));
}
}

lexer::Token lexer::Lexer::lex_less_than() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue(lexer::Token::LessThanOrEqual(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'<')) {
return JaktInternal::ExplicitValue(({ Optional<lexer::Token> __jakt_var_5; {
((((*this).index)++));
__jakt_var_5 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'<')) {
return JaktInternal::ExplicitValue(lexer::Token::LeftArithmeticShift(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue(lexer::Token::LeftShiftEqual(((*this).span(start,(++(((*this).index)))))));
}
else {
return JaktInternal::ExplicitValue(lexer::Token::LeftShift(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_1;

}
__jakt_label_1:; __jakt_var_5.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(lexer::Token::LessThan(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

bool lexer::Lexer::eof() const {
{
return [](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(((*this).index),((((*this).input)).size()));
}
}

lexer::Lexer::Lexer(size_t a_index, JaktInternal::DynamicArray<u8> a_input, NonnullRefPtr<compiler::Compiler> a_compiler, JaktInternal::Optional<JaktInternal::DynamicArray<u8>> a_comment_contents, JaktInternal::Set<DeprecatedString> a_illegal_cpp_keywords) :index(move(a_index)), input(move(a_input)), compiler(move(a_compiler)), comment_contents(move(a_comment_contents)), illegal_cpp_keywords(move(a_illegal_cpp_keywords)){}

lexer::Token lexer::Lexer::lex_ampersand() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue(lexer::Token::AmpersandEqual(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'&')) {
return JaktInternal::ExplicitValue(lexer::Token::AmpersandAmpersand(((*this).span(start,(++(((*this).index)))))));
}
else {
return JaktInternal::ExplicitValue(lexer::Token::Ampersand(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

utility::Span lexer::Lexer::span(size_t const start,size_t const end) const {
{
return utility::Span((((((*this).compiler))->current_file).value()),start,end);
}
}

lexer::Token lexer::Lexer::lex_plus() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue(lexer::Token::PlusEqual(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'+')) {
return JaktInternal::ExplicitValue(lexer::Token::PlusPlus(((*this).span(start,(++(((*this).index)))))));
}
else {
return JaktInternal::ExplicitValue(lexer::Token::Plus(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

lexer::Token lexer::Lexer::lex_exclamation_point() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue(lexer::Token::NotEqual(((*this).span(start,(++(((*this).index)))))));
}
else {
return JaktInternal::ExplicitValue(lexer::Token::ExclamationPoint(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<lexer::LiteralSuffix> lexer::Lexer::consume_numeric_literal_suffix() {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<lexer::LiteralSuffix>>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'u')) {
{
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == static_cast<u8>(u8'i')) {
{
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == static_cast<u8>(u8'f')) {
{
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
return lexer::LiteralSuffix::None();
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if ((((((*this).peek())) == (static_cast<u8>(u8'u'))) && ((((*this).peek_ahead(static_cast<size_t>(1ULL)))) == (static_cast<u8>(u8'z'))))){
((((*this).index)) += (static_cast<size_t>(2ULL)));
return lexer::LiteralSuffix::UZ();
}
size_t local_index = static_cast<size_t>(1ULL);
i64 width = static_cast<i64>(0LL);
while (utility::is_ascii_digit(((*this).peek_ahead(local_index)))){
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(local_index,static_cast<size_t>(3ULL))){
return lexer::LiteralSuffix::None();
}
u8 const value = ((((*this).input))[JaktInternal::checked_add(((*this).index),local_index)]);
(++(local_index));
i64 const digit = as_saturated<i64, u8>(JaktInternal::checked_sub(value,static_cast<u8>(u8'0')));
(width = JaktInternal::checked_add(JaktInternal::checked_mul(width,static_cast<i64>(10LL)),digit));
}
lexer::LiteralSuffix const suffix = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::LiteralSuffix,ErrorOr<lexer::LiteralSuffix>>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'u')) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::LiteralSuffix,ErrorOr<lexer::LiteralSuffix>>{
auto __jakt_enum_value = (width);
if (__jakt_enum_value == static_cast<i64>(8LL)) {
return JaktInternal::ExplicitValue(lexer::LiteralSuffix::U8());
}
else if (__jakt_enum_value == static_cast<i64>(16LL)) {
return JaktInternal::ExplicitValue(lexer::LiteralSuffix::U16());
}
else if (__jakt_enum_value == static_cast<i64>(32LL)) {
return JaktInternal::ExplicitValue(lexer::LiteralSuffix::U32());
}
else if (__jakt_enum_value == static_cast<i64>(64LL)) {
return JaktInternal::ExplicitValue(lexer::LiteralSuffix::U64());
}
else {
return JaktInternal::ExplicitValue(lexer::LiteralSuffix::None());
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == static_cast<u8>(u8'i')) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::LiteralSuffix,ErrorOr<lexer::LiteralSuffix>>{
auto __jakt_enum_value = (width);
if (__jakt_enum_value == static_cast<i64>(8LL)) {
return JaktInternal::ExplicitValue(lexer::LiteralSuffix::I8());
}
else if (__jakt_enum_value == static_cast<i64>(16LL)) {
return JaktInternal::ExplicitValue(lexer::LiteralSuffix::I16());
}
else if (__jakt_enum_value == static_cast<i64>(32LL)) {
return JaktInternal::ExplicitValue(lexer::LiteralSuffix::I32());
}
else if (__jakt_enum_value == static_cast<i64>(64LL)) {
return JaktInternal::ExplicitValue(lexer::LiteralSuffix::I64());
}
else {
return JaktInternal::ExplicitValue(lexer::LiteralSuffix::None());
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == static_cast<u8>(u8'f')) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::LiteralSuffix,ErrorOr<lexer::LiteralSuffix>>{
auto __jakt_enum_value = (width);
if (__jakt_enum_value == static_cast<i64>(32LL)) {
return JaktInternal::ExplicitValue(lexer::LiteralSuffix::F32());
}
else if (__jakt_enum_value == static_cast<i64>(64LL)) {
return JaktInternal::ExplicitValue(lexer::LiteralSuffix::F64());
}
else {
return JaktInternal::ExplicitValue(lexer::LiteralSuffix::None());
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else {
return JaktInternal::ExplicitValue(lexer::LiteralSuffix::None());
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if ((!(((suffix).__jakt_init_index() == 0 /* None */)))){
((((*this).index)) += (local_index));
}
return suffix;
}
}

lexer::Token lexer::Lexer::lex_colon() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8':')) {
return JaktInternal::ExplicitValue(lexer::Token::ColonColon(((*this).span(start,(++(((*this).index)))))));
}
else {
return JaktInternal::ExplicitValue(lexer::Token::Colon(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

bool lexer::Lexer::valid_digit(lexer::LiteralPrefix const prefix,u8 const digit,bool const decimal_allowed) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = prefix;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Hexadecimal */: {
return JaktInternal::ExplicitValue(utility::is_ascii_hexdigit(digit));
};/*case end*/
case 2 /* Octal */: {
return JaktInternal::ExplicitValue(utility::is_ascii_octdigit(digit));
};/*case end*/
case 3 /* Binary */: {
return JaktInternal::ExplicitValue(utility::is_ascii_binary(digit));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((utility::is_ascii_digit(digit) || (decimal_allowed && ((digit) == (static_cast<u8>(u8'.'))))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<void> lexer::Lexer::error(DeprecatedString const message,utility::Span const span) {
{
TRY((((((((*this).compiler))->errors)).push(error::JaktError::Message(message,span)))));
}
return {};
}

lexer::Token lexer::Lexer::lex_equals() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue(lexer::Token::DoubleEqual(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'>')) {
return JaktInternal::ExplicitValue(lexer::Token::FatArrow(((*this).span(start,(++(((*this).index)))))));
}
else {
return JaktInternal::ExplicitValue(lexer::Token::Equal(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<DeprecatedString> lexer::Lexer::substring(size_t const start,size_t const length) const {
{
DeprecatedStringBuilder builder = DeprecatedStringBuilder::create();
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(start),static_cast<size_t>(length)});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
TRY((((builder).append(((((*this).input))[i])))));
}

}
}

return TRY((((builder).to_string())));
}
}

lexer::Token lexer::Lexer::lex_greater_than() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue(lexer::Token::GreaterThanOrEqual(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'>')) {
return JaktInternal::ExplicitValue(({ Optional<lexer::Token> __jakt_var_6; {
((((*this).index)++));
__jakt_var_6 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'>')) {
return JaktInternal::ExplicitValue(lexer::Token::RightArithmeticShift(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue(lexer::Token::RightShiftEqual(((*this).span(start,(++(((*this).index)))))));
}
else {
return JaktInternal::ExplicitValue(lexer::Token::RightShift(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_2;

}
__jakt_label_2:; __jakt_var_6.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(lexer::Token::GreaterThan(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

lexer::Token lexer::Lexer::lex_pipe() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue(lexer::Token::PipeEqual(((*this).span(start,(++(((*this).index)))))));
}
else if (__jakt_enum_value == static_cast<u8>(u8'|')) {
return JaktInternal::ExplicitValue(lexer::Token::PipePipe(((*this).span(start,(++(((*this).index)))))));
}
else {
return JaktInternal::ExplicitValue(lexer::Token::Pipe(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

lexer::Token lexer::Lexer::lex_caret() {
{
size_t const start = ((((*this).index)++));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,lexer::Token>{
auto __jakt_enum_value = (((*this).peek()));
if (__jakt_enum_value == static_cast<u8>(u8'=')) {
return JaktInternal::ExplicitValue(lexer::Token::CaretEqual(((*this).span(start,(++(((*this).index)))))));
}
else {
return JaktInternal::ExplicitValue(lexer::Token::Caret(((*this).span(JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL)),((*this).index)))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<lexer::Token> lexer::Lexer::lex_number() {
{
size_t const start = ((*this).index);
bool floating = false;
lexer::LiteralPrefix prefix = lexer::LiteralPrefix::None();
DeprecatedStringBuilder number = DeprecatedStringBuilder::create();
if (((((*this).peek())) == (static_cast<u8>(u8'0')))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<lexer::Token>>{
auto __jakt_enum_value = (((*this).peek_ahead(static_cast<size_t>(1ULL))));
if (__jakt_enum_value == static_cast<u8>(u8'x')) {
{
(prefix = lexer::LiteralPrefix::Hexadecimal());
((((*this).index)) += (static_cast<size_t>(2ULL)));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == static_cast<u8>(u8'o')) {
{
(prefix = lexer::LiteralPrefix::Octal());
((((*this).index)) += (static_cast<size_t>(2ULL)));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == static_cast<u8>(u8'b')) {
{
(prefix = lexer::LiteralPrefix::Binary());
((((*this).index)) += (static_cast<size_t>(2ULL)));
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
while ((!(((*this).eof())))){
u8 const value = ((((*this).input))[((*this).index)]);
if ((!(((*this).valid_digit(prefix,value,true))))){
break;
}
if (((value) == (static_cast<u8>(u8'.')))){
if ((floating || (!(((*this).valid_digit(prefix,((*this).peek_ahead(static_cast<size_t>(1ULL))),false)))))){
break;
}
TRY((((number).append(static_cast<u8>(u8'.')))));
(floating = true);
((((*this).index)++));
continue;
}
TRY((((number).append(value))));
(++(((*this).index)));
if (((((*this).peek())) == (static_cast<u8>(u8'_')))){
TRY((((number).append(static_cast<u8>(u8'_')))));
if (((*this).valid_digit(prefix,((*this).peek_ahead(static_cast<size_t>(1ULL))),true))){
(++(((*this).index)));
}
else {
break;
}

}
}
lexer::LiteralSuffix const suffix = TRY((((*this).consume_numeric_literal_suffix())));
return lexer::Token::Number(prefix,TRY((((number).to_string()))),suffix,((*this).span(start,((*this).index))));
}
}

ErrorOr<JaktInternal::DynamicArray<lexer::Token>> lexer::Lexer::lex(NonnullRefPtr<compiler::Compiler> const compiler) {
{
JaktInternal::Set<DeprecatedString> const illegal_cpp_keywords = (TRY((Set<DeprecatedString>::create_with_values({TRY(DeprecatedString::from_utf8("alignas"sv)), TRY(DeprecatedString::from_utf8("alignof"sv)), TRY(DeprecatedString::from_utf8("and_eq"sv)), TRY(DeprecatedString::from_utf8("asm"sv)), TRY(DeprecatedString::from_utf8("auto"sv)), TRY(DeprecatedString::from_utf8("bitand"sv)), TRY(DeprecatedString::from_utf8("bitor"sv)), TRY(DeprecatedString::from_utf8("case"sv)), TRY(DeprecatedString::from_utf8("char"sv)), TRY(DeprecatedString::from_utf8("char8_t"sv)), TRY(DeprecatedString::from_utf8("char16_t"sv)), TRY(DeprecatedString::from_utf8("char32_t"sv)), TRY(DeprecatedString::from_utf8("compl"sv)), TRY(DeprecatedString::from_utf8("concept"sv)), TRY(DeprecatedString::from_utf8("consteval"sv)), TRY(DeprecatedString::from_utf8("constexpr"sv)), TRY(DeprecatedString::from_utf8("constinit"sv)), TRY(DeprecatedString::from_utf8("const_cast"sv)), TRY(DeprecatedString::from_utf8("co_await"sv)), TRY(DeprecatedString::from_utf8("co_return"sv)), TRY(DeprecatedString::from_utf8("co_yield"sv)), TRY(DeprecatedString::from_utf8("decltype"sv)), TRY(DeprecatedString::from_utf8("delete"sv)), TRY(DeprecatedString::from_utf8("do"sv)), TRY(DeprecatedString::from_utf8("double"sv)), TRY(DeprecatedString::from_utf8("dynamic_cast"sv)), TRY(DeprecatedString::from_utf8("explicit"sv)), TRY(DeprecatedString::from_utf8("export"sv)), TRY(DeprecatedString::from_utf8("float"sv)), TRY(DeprecatedString::from_utf8("friend"sv)), TRY(DeprecatedString::from_utf8("goto"sv)), TRY(DeprecatedString::from_utf8("int"sv)), TRY(DeprecatedString::from_utf8("long"sv)), TRY(DeprecatedString::from_utf8("mutable"sv)), TRY(DeprecatedString::from_utf8("new"sv)), TRY(DeprecatedString::from_utf8("noexcept"sv)), TRY(DeprecatedString::from_utf8("not_eq"sv)), TRY(DeprecatedString::from_utf8("nullptr"sv)), TRY(DeprecatedString::from_utf8("operator"sv)), TRY(DeprecatedString::from_utf8("or_eq"sv)), TRY(DeprecatedString::from_utf8("protected"sv)), TRY(DeprecatedString::from_utf8("register"sv)), TRY(DeprecatedString::from_utf8("reinterpret_cast"sv)), TRY(DeprecatedString::from_utf8("short"sv)), TRY(DeprecatedString::from_utf8("signed"sv)), TRY(DeprecatedString::from_utf8("static"sv)), TRY(DeprecatedString::from_utf8("static_assert"sv)), TRY(DeprecatedString::from_utf8("static_cast"sv)), TRY(DeprecatedString::from_utf8("switch"sv)), TRY(DeprecatedString::from_utf8("template"sv)), TRY(DeprecatedString::from_utf8("thread_local"sv)), TRY(DeprecatedString::from_utf8("typedef"sv)), TRY(DeprecatedString::from_utf8("typeid"sv)), TRY(DeprecatedString::from_utf8("typename"sv)), TRY(DeprecatedString::from_utf8("union"sv)), TRY(DeprecatedString::from_utf8("unsigned"sv)), TRY(DeprecatedString::from_utf8("using"sv)), TRY(DeprecatedString::from_utf8("volatile"sv)), TRY(DeprecatedString::from_utf8("wchar_t"sv)), TRY(DeprecatedString::from_utf8("xor"sv)), TRY(DeprecatedString::from_utf8("xor_eq"sv))}))));
lexer::Lexer lexer = lexer::Lexer(static_cast<size_t>(0ULL),((compiler)->current_file_contents),compiler,JaktInternal::OptionalNone(),illegal_cpp_keywords);
JaktInternal::DynamicArray<lexer::Token> tokens = (TRY((DynamicArray<lexer::Token>::create_with({}))));
{
lexer::Lexer _magic = lexer;
for (;;){
JaktInternal::Optional<lexer::Token> const _magic_value = TRY((((_magic).next())));
if ((!(((_magic_value).has_value())))){
break;
}
lexer::Token token = (_magic_value.value());
{
TRY((((tokens).push(token))));
}

}
}

return tokens;
}
}

ErrorOr<DeprecatedString> lexer::LiteralSuffix::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* None */: {
return DeprecatedString("LiteralSuffix::None"sv);
break;}
case 1 /* UZ */: {
return DeprecatedString("LiteralSuffix::UZ"sv);
break;}
case 2 /* U8 */: {
return DeprecatedString("LiteralSuffix::U8"sv);
break;}
case 3 /* U16 */: {
return DeprecatedString("LiteralSuffix::U16"sv);
break;}
case 4 /* U32 */: {
return DeprecatedString("LiteralSuffix::U32"sv);
break;}
case 5 /* U64 */: {
return DeprecatedString("LiteralSuffix::U64"sv);
break;}
case 6 /* I8 */: {
return DeprecatedString("LiteralSuffix::I8"sv);
break;}
case 7 /* I16 */: {
return DeprecatedString("LiteralSuffix::I16"sv);
break;}
case 8 /* I32 */: {
return DeprecatedString("LiteralSuffix::I32"sv);
break;}
case 9 /* I64 */: {
return DeprecatedString("LiteralSuffix::I64"sv);
break;}
case 10 /* F32 */: {
return DeprecatedString("LiteralSuffix::F32"sv);
break;}
case 11 /* F64 */: {
return DeprecatedString("LiteralSuffix::F64"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] LiteralSuffix LiteralSuffix::None(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::UZ(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::U8(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::U16(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::U32(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 5;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::U64(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 6;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::I8(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 7;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::I16(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 8;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::I32(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 9;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::I64(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 10;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::F32(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 11;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralSuffix LiteralSuffix::F64(){
LiteralSuffix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 12;
return __jakt_uninit_enum;
}
LiteralSuffix& LiteralSuffix::operator=(LiteralSuffix const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* UZ */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* UZ */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
LiteralSuffix::LiteralSuffix(LiteralSuffix const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* UZ */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
LiteralSuffix& LiteralSuffix::operator=(LiteralSuffix &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* UZ */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* UZ */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
LiteralSuffix::LiteralSuffix(LiteralSuffix &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* UZ */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
LiteralSuffix::~LiteralSuffix(){
if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant();
}
void LiteralSuffix::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* None */:break;
case 1 /* UZ */:break;
case 2 /* U8 */:break;
case 3 /* U16 */:break;
case 4 /* U32 */:break;
case 5 /* U64 */:break;
case 6 /* I8 */:break;
case 7 /* I16 */:break;
case 8 /* I32 */:break;
case 9 /* I64 */:break;
case 10 /* F32 */:break;
case 11 /* F64 */:break;
}
}
ErrorOr<DeprecatedString> lexer::LiteralSuffix::to_string() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString, ErrorOr<DeprecatedString>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* None */: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(""sv)));
};/*case end*/
case 1 /* UZ */: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("uz"sv)));
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("u8"sv)));
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("u16"sv)));
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("u32"sv)));
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("u64"sv)));
};/*case end*/
case 6 /* I8 */: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("i8"sv)));
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("i16"sv)));
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("i32"sv)));
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("i64"sv)));
};/*case end*/
case 10 /* F32 */: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("f32"sv)));
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("f64"sv)));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<DeprecatedString> lexer::Token::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* SingleQuotedString */: {
TRY(builder.append("Token::SingleQuotedString"sv));
[[maybe_unused]] auto const& that = this->as.SingleQuotedString;
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("quote: \"{}\", ", that.quote));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("prefix: {}, ", that.prefix));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 1 /* QuotedString */: {
TRY(builder.append("Token::QuotedString"sv));
[[maybe_unused]] auto const& that = this->as.QuotedString;
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("quote: \"{}\", ", that.quote));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 2 /* Number */: {
TRY(builder.append("Token::Number"sv));
[[maybe_unused]] auto const& that = this->as.Number;
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("prefix: {}, ", that.prefix));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("number: \"{}\", ", that.number));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("suffix: {}, ", that.suffix));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 3 /* Identifier */: {
TRY(builder.append("Token::Identifier"sv));
[[maybe_unused]] auto const& that = this->as.Identifier;
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("name: \"{}\", ", that.name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 4 /* Semicolon */: {
TRY(builder.append("Token::Semicolon"sv));
[[maybe_unused]] auto const& that = this->as.Semicolon;
TRY(builder.appendff("({})", that.value));
break;}
case 5 /* Colon */: {
TRY(builder.append("Token::Colon"sv));
[[maybe_unused]] auto const& that = this->as.Colon;
TRY(builder.appendff("({})", that.value));
break;}
case 6 /* ColonColon */: {
TRY(builder.append("Token::ColonColon"sv));
[[maybe_unused]] auto const& that = this->as.ColonColon;
TRY(builder.appendff("({})", that.value));
break;}
case 7 /* LParen */: {
TRY(builder.append("Token::LParen"sv));
[[maybe_unused]] auto const& that = this->as.LParen;
TRY(builder.appendff("({})", that.value));
break;}
case 8 /* RParen */: {
TRY(builder.append("Token::RParen"sv));
[[maybe_unused]] auto const& that = this->as.RParen;
TRY(builder.appendff("({})", that.value));
break;}
case 9 /* LCurly */: {
TRY(builder.append("Token::LCurly"sv));
[[maybe_unused]] auto const& that = this->as.LCurly;
TRY(builder.appendff("({})", that.value));
break;}
case 10 /* RCurly */: {
TRY(builder.append("Token::RCurly"sv));
[[maybe_unused]] auto const& that = this->as.RCurly;
TRY(builder.appendff("({})", that.value));
break;}
case 11 /* LSquare */: {
TRY(builder.append("Token::LSquare"sv));
[[maybe_unused]] auto const& that = this->as.LSquare;
TRY(builder.appendff("({})", that.value));
break;}
case 12 /* RSquare */: {
TRY(builder.append("Token::RSquare"sv));
[[maybe_unused]] auto const& that = this->as.RSquare;
TRY(builder.appendff("({})", that.value));
break;}
case 13 /* PercentSign */: {
TRY(builder.append("Token::PercentSign"sv));
[[maybe_unused]] auto const& that = this->as.PercentSign;
TRY(builder.appendff("({})", that.value));
break;}
case 14 /* Plus */: {
TRY(builder.append("Token::Plus"sv));
[[maybe_unused]] auto const& that = this->as.Plus;
TRY(builder.appendff("({})", that.value));
break;}
case 15 /* Minus */: {
TRY(builder.append("Token::Minus"sv));
[[maybe_unused]] auto const& that = this->as.Minus;
TRY(builder.appendff("({})", that.value));
break;}
case 16 /* Equal */: {
TRY(builder.append("Token::Equal"sv));
[[maybe_unused]] auto const& that = this->as.Equal;
TRY(builder.appendff("({})", that.value));
break;}
case 17 /* PlusEqual */: {
TRY(builder.append("Token::PlusEqual"sv));
[[maybe_unused]] auto const& that = this->as.PlusEqual;
TRY(builder.appendff("({})", that.value));
break;}
case 18 /* PlusPlus */: {
TRY(builder.append("Token::PlusPlus"sv));
[[maybe_unused]] auto const& that = this->as.PlusPlus;
TRY(builder.appendff("({})", that.value));
break;}
case 19 /* MinusEqual */: {
TRY(builder.append("Token::MinusEqual"sv));
[[maybe_unused]] auto const& that = this->as.MinusEqual;
TRY(builder.appendff("({})", that.value));
break;}
case 20 /* MinusMinus */: {
TRY(builder.append("Token::MinusMinus"sv));
[[maybe_unused]] auto const& that = this->as.MinusMinus;
TRY(builder.appendff("({})", that.value));
break;}
case 21 /* AsteriskEqual */: {
TRY(builder.append("Token::AsteriskEqual"sv));
[[maybe_unused]] auto const& that = this->as.AsteriskEqual;
TRY(builder.appendff("({})", that.value));
break;}
case 22 /* ForwardSlashEqual */: {
TRY(builder.append("Token::ForwardSlashEqual"sv));
[[maybe_unused]] auto const& that = this->as.ForwardSlashEqual;
TRY(builder.appendff("({})", that.value));
break;}
case 23 /* PercentSignEqual */: {
TRY(builder.append("Token::PercentSignEqual"sv));
[[maybe_unused]] auto const& that = this->as.PercentSignEqual;
TRY(builder.appendff("({})", that.value));
break;}
case 24 /* NotEqual */: {
TRY(builder.append("Token::NotEqual"sv));
[[maybe_unused]] auto const& that = this->as.NotEqual;
TRY(builder.appendff("({})", that.value));
break;}
case 25 /* DoubleEqual */: {
TRY(builder.append("Token::DoubleEqual"sv));
[[maybe_unused]] auto const& that = this->as.DoubleEqual;
TRY(builder.appendff("({})", that.value));
break;}
case 26 /* GreaterThan */: {
TRY(builder.append("Token::GreaterThan"sv));
[[maybe_unused]] auto const& that = this->as.GreaterThan;
TRY(builder.appendff("({})", that.value));
break;}
case 27 /* GreaterThanOrEqual */: {
TRY(builder.append("Token::GreaterThanOrEqual"sv));
[[maybe_unused]] auto const& that = this->as.GreaterThanOrEqual;
TRY(builder.appendff("({})", that.value));
break;}
case 28 /* LessThan */: {
TRY(builder.append("Token::LessThan"sv));
[[maybe_unused]] auto const& that = this->as.LessThan;
TRY(builder.appendff("({})", that.value));
break;}
case 29 /* LessThanOrEqual */: {
TRY(builder.append("Token::LessThanOrEqual"sv));
[[maybe_unused]] auto const& that = this->as.LessThanOrEqual;
TRY(builder.appendff("({})", that.value));
break;}
case 30 /* LeftArithmeticShift */: {
TRY(builder.append("Token::LeftArithmeticShift"sv));
[[maybe_unused]] auto const& that = this->as.LeftArithmeticShift;
TRY(builder.appendff("({})", that.value));
break;}
case 31 /* LeftShift */: {
TRY(builder.append("Token::LeftShift"sv));
[[maybe_unused]] auto const& that = this->as.LeftShift;
TRY(builder.appendff("({})", that.value));
break;}
case 32 /* LeftShiftEqual */: {
TRY(builder.append("Token::LeftShiftEqual"sv));
[[maybe_unused]] auto const& that = this->as.LeftShiftEqual;
TRY(builder.appendff("({})", that.value));
break;}
case 33 /* RightShift */: {
TRY(builder.append("Token::RightShift"sv));
[[maybe_unused]] auto const& that = this->as.RightShift;
TRY(builder.appendff("({})", that.value));
break;}
case 34 /* RightArithmeticShift */: {
TRY(builder.append("Token::RightArithmeticShift"sv));
[[maybe_unused]] auto const& that = this->as.RightArithmeticShift;
TRY(builder.appendff("({})", that.value));
break;}
case 35 /* RightShiftEqual */: {
TRY(builder.append("Token::RightShiftEqual"sv));
[[maybe_unused]] auto const& that = this->as.RightShiftEqual;
TRY(builder.appendff("({})", that.value));
break;}
case 36 /* Asterisk */: {
TRY(builder.append("Token::Asterisk"sv));
[[maybe_unused]] auto const& that = this->as.Asterisk;
TRY(builder.appendff("({})", that.value));
break;}
case 37 /* Ampersand */: {
TRY(builder.append("Token::Ampersand"sv));
[[maybe_unused]] auto const& that = this->as.Ampersand;
TRY(builder.appendff("({})", that.value));
break;}
case 38 /* AmpersandEqual */: {
TRY(builder.append("Token::AmpersandEqual"sv));
[[maybe_unused]] auto const& that = this->as.AmpersandEqual;
TRY(builder.appendff("({})", that.value));
break;}
case 39 /* AmpersandAmpersand */: {
TRY(builder.append("Token::AmpersandAmpersand"sv));
[[maybe_unused]] auto const& that = this->as.AmpersandAmpersand;
TRY(builder.appendff("({})", that.value));
break;}
case 40 /* Pipe */: {
TRY(builder.append("Token::Pipe"sv));
[[maybe_unused]] auto const& that = this->as.Pipe;
TRY(builder.appendff("({})", that.value));
break;}
case 41 /* PipeEqual */: {
TRY(builder.append("Token::PipeEqual"sv));
[[maybe_unused]] auto const& that = this->as.PipeEqual;
TRY(builder.appendff("({})", that.value));
break;}
case 42 /* PipePipe */: {
TRY(builder.append("Token::PipePipe"sv));
[[maybe_unused]] auto const& that = this->as.PipePipe;
TRY(builder.appendff("({})", that.value));
break;}
case 43 /* Caret */: {
TRY(builder.append("Token::Caret"sv));
[[maybe_unused]] auto const& that = this->as.Caret;
TRY(builder.appendff("({})", that.value));
break;}
case 44 /* CaretEqual */: {
TRY(builder.append("Token::CaretEqual"sv));
[[maybe_unused]] auto const& that = this->as.CaretEqual;
TRY(builder.appendff("({})", that.value));
break;}
case 45 /* Dollar */: {
TRY(builder.append("Token::Dollar"sv));
[[maybe_unused]] auto const& that = this->as.Dollar;
TRY(builder.appendff("({})", that.value));
break;}
case 46 /* Tilde */: {
TRY(builder.append("Token::Tilde"sv));
[[maybe_unused]] auto const& that = this->as.Tilde;
TRY(builder.appendff("({})", that.value));
break;}
case 47 /* ForwardSlash */: {
TRY(builder.append("Token::ForwardSlash"sv));
[[maybe_unused]] auto const& that = this->as.ForwardSlash;
TRY(builder.appendff("({})", that.value));
break;}
case 48 /* ExclamationPoint */: {
TRY(builder.append("Token::ExclamationPoint"sv));
[[maybe_unused]] auto const& that = this->as.ExclamationPoint;
TRY(builder.appendff("({})", that.value));
break;}
case 49 /* QuestionMark */: {
TRY(builder.append("Token::QuestionMark"sv));
[[maybe_unused]] auto const& that = this->as.QuestionMark;
TRY(builder.appendff("({})", that.value));
break;}
case 50 /* QuestionMarkQuestionMark */: {
TRY(builder.append("Token::QuestionMarkQuestionMark"sv));
[[maybe_unused]] auto const& that = this->as.QuestionMarkQuestionMark;
TRY(builder.appendff("({})", that.value));
break;}
case 51 /* QuestionMarkQuestionMarkEqual */: {
TRY(builder.append("Token::QuestionMarkQuestionMarkEqual"sv));
[[maybe_unused]] auto const& that = this->as.QuestionMarkQuestionMarkEqual;
TRY(builder.appendff("({})", that.value));
break;}
case 52 /* Comma */: {
TRY(builder.append("Token::Comma"sv));
[[maybe_unused]] auto const& that = this->as.Comma;
TRY(builder.appendff("({})", that.value));
break;}
case 53 /* Dot */: {
TRY(builder.append("Token::Dot"sv));
[[maybe_unused]] auto const& that = this->as.Dot;
TRY(builder.appendff("({})", that.value));
break;}
case 54 /* DotDot */: {
TRY(builder.append("Token::DotDot"sv));
[[maybe_unused]] auto const& that = this->as.DotDot;
TRY(builder.appendff("({})", that.value));
break;}
case 55 /* Eol */: {
TRY(builder.append("Token::Eol"sv));
[[maybe_unused]] auto const& that = this->as.Eol;
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("comment: {}, ", that.comment));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 56 /* Eof */: {
TRY(builder.append("Token::Eof"sv));
[[maybe_unused]] auto const& that = this->as.Eof;
TRY(builder.appendff("({})", that.value));
break;}
case 57 /* FatArrow */: {
TRY(builder.append("Token::FatArrow"sv));
[[maybe_unused]] auto const& that = this->as.FatArrow;
TRY(builder.appendff("({})", that.value));
break;}
case 58 /* Arrow */: {
TRY(builder.append("Token::Arrow"sv));
[[maybe_unused]] auto const& that = this->as.Arrow;
TRY(builder.appendff("({})", that.value));
break;}
case 59 /* And */: {
TRY(builder.append("Token::And"sv));
[[maybe_unused]] auto const& that = this->as.And;
TRY(builder.appendff("({})", that.value));
break;}
case 60 /* Anon */: {
TRY(builder.append("Token::Anon"sv));
[[maybe_unused]] auto const& that = this->as.Anon;
TRY(builder.appendff("({})", that.value));
break;}
case 61 /* As */: {
TRY(builder.append("Token::As"sv));
[[maybe_unused]] auto const& that = this->as.As;
TRY(builder.appendff("({})", that.value));
break;}
case 62 /* Boxed */: {
TRY(builder.append("Token::Boxed"sv));
[[maybe_unused]] auto const& that = this->as.Boxed;
TRY(builder.appendff("({})", that.value));
break;}
case 63 /* Break */: {
TRY(builder.append("Token::Break"sv));
[[maybe_unused]] auto const& that = this->as.Break;
TRY(builder.appendff("({})", that.value));
break;}
case 64 /* Catch */: {
TRY(builder.append("Token::Catch"sv));
[[maybe_unused]] auto const& that = this->as.Catch;
TRY(builder.appendff("({})", that.value));
break;}
case 65 /* Class */: {
TRY(builder.append("Token::Class"sv));
[[maybe_unused]] auto const& that = this->as.Class;
TRY(builder.appendff("({})", that.value));
break;}
case 66 /* Continue */: {
TRY(builder.append("Token::Continue"sv));
[[maybe_unused]] auto const& that = this->as.Continue;
TRY(builder.appendff("({})", that.value));
break;}
case 67 /* Cpp */: {
TRY(builder.append("Token::Cpp"sv));
[[maybe_unused]] auto const& that = this->as.Cpp;
TRY(builder.appendff("({})", that.value));
break;}
case 68 /* Defer */: {
TRY(builder.append("Token::Defer"sv));
[[maybe_unused]] auto const& that = this->as.Defer;
TRY(builder.appendff("({})", that.value));
break;}
case 69 /* Destructor */: {
TRY(builder.append("Token::Destructor"sv));
[[maybe_unused]] auto const& that = this->as.Destructor;
TRY(builder.appendff("({})", that.value));
break;}
case 70 /* Else */: {
TRY(builder.append("Token::Else"sv));
[[maybe_unused]] auto const& that = this->as.Else;
TRY(builder.appendff("({})", that.value));
break;}
case 71 /* Enum */: {
TRY(builder.append("Token::Enum"sv));
[[maybe_unused]] auto const& that = this->as.Enum;
TRY(builder.appendff("({})", that.value));
break;}
case 72 /* Extern */: {
TRY(builder.append("Token::Extern"sv));
[[maybe_unused]] auto const& that = this->as.Extern;
TRY(builder.appendff("({})", that.value));
break;}
case 73 /* False */: {
TRY(builder.append("Token::False"sv));
[[maybe_unused]] auto const& that = this->as.False;
TRY(builder.appendff("({})", that.value));
break;}
case 74 /* For */: {
TRY(builder.append("Token::For"sv));
[[maybe_unused]] auto const& that = this->as.For;
TRY(builder.appendff("({})", that.value));
break;}
case 75 /* Fn */: {
TRY(builder.append("Token::Fn"sv));
[[maybe_unused]] auto const& that = this->as.Fn;
TRY(builder.appendff("({})", that.value));
break;}
case 76 /* Comptime */: {
TRY(builder.append("Token::Comptime"sv));
[[maybe_unused]] auto const& that = this->as.Comptime;
TRY(builder.appendff("({})", that.value));
break;}
case 77 /* If */: {
TRY(builder.append("Token::If"sv));
[[maybe_unused]] auto const& that = this->as.If;
TRY(builder.appendff("({})", that.value));
break;}
case 78 /* Import */: {
TRY(builder.append("Token::Import"sv));
[[maybe_unused]] auto const& that = this->as.Import;
TRY(builder.appendff("({})", that.value));
break;}
case 79 /* In */: {
TRY(builder.append("Token::In"sv));
[[maybe_unused]] auto const& that = this->as.In;
TRY(builder.appendff("({})", that.value));
break;}
case 80 /* Is */: {
TRY(builder.append("Token::Is"sv));
[[maybe_unused]] auto const& that = this->as.Is;
TRY(builder.appendff("({})", that.value));
break;}
case 81 /* Let */: {
TRY(builder.append("Token::Let"sv));
[[maybe_unused]] auto const& that = this->as.Let;
TRY(builder.appendff("({})", that.value));
break;}
case 82 /* Loop */: {
TRY(builder.append("Token::Loop"sv));
[[maybe_unused]] auto const& that = this->as.Loop;
TRY(builder.appendff("({})", that.value));
break;}
case 83 /* Match */: {
TRY(builder.append("Token::Match"sv));
[[maybe_unused]] auto const& that = this->as.Match;
TRY(builder.appendff("({})", that.value));
break;}
case 84 /* Mut */: {
TRY(builder.append("Token::Mut"sv));
[[maybe_unused]] auto const& that = this->as.Mut;
TRY(builder.appendff("({})", that.value));
break;}
case 85 /* Namespace */: {
TRY(builder.append("Token::Namespace"sv));
[[maybe_unused]] auto const& that = this->as.Namespace;
TRY(builder.appendff("({})", that.value));
break;}
case 86 /* Not */: {
TRY(builder.append("Token::Not"sv));
[[maybe_unused]] auto const& that = this->as.Not;
TRY(builder.appendff("({})", that.value));
break;}
case 87 /* Or */: {
TRY(builder.append("Token::Or"sv));
[[maybe_unused]] auto const& that = this->as.Or;
TRY(builder.appendff("({})", that.value));
break;}
case 88 /* Override */: {
TRY(builder.append("Token::Override"sv));
[[maybe_unused]] auto const& that = this->as.Override;
TRY(builder.appendff("({})", that.value));
break;}
case 89 /* Private */: {
TRY(builder.append("Token::Private"sv));
[[maybe_unused]] auto const& that = this->as.Private;
TRY(builder.appendff("({})", that.value));
break;}
case 90 /* Public */: {
TRY(builder.append("Token::Public"sv));
[[maybe_unused]] auto const& that = this->as.Public;
TRY(builder.appendff("({})", that.value));
break;}
case 91 /* Raw */: {
TRY(builder.append("Token::Raw"sv));
[[maybe_unused]] auto const& that = this->as.Raw;
TRY(builder.appendff("({})", that.value));
break;}
case 92 /* Reflect */: {
TRY(builder.append("Token::Reflect"sv));
[[maybe_unused]] auto const& that = this->as.Reflect;
TRY(builder.appendff("({})", that.value));
break;}
case 93 /* Return */: {
TRY(builder.append("Token::Return"sv));
[[maybe_unused]] auto const& that = this->as.Return;
TRY(builder.appendff("({})", that.value));
break;}
case 94 /* Restricted */: {
TRY(builder.append("Token::Restricted"sv));
[[maybe_unused]] auto const& that = this->as.Restricted;
TRY(builder.appendff("({})", that.value));
break;}
case 95 /* Sizeof */: {
TRY(builder.append("Token::Sizeof"sv));
[[maybe_unused]] auto const& that = this->as.Sizeof;
TRY(builder.appendff("({})", that.value));
break;}
case 96 /* Struct */: {
TRY(builder.append("Token::Struct"sv));
[[maybe_unused]] auto const& that = this->as.Struct;
TRY(builder.appendff("({})", that.value));
break;}
case 97 /* This */: {
TRY(builder.append("Token::This"sv));
[[maybe_unused]] auto const& that = this->as.This;
TRY(builder.appendff("({})", that.value));
break;}
case 98 /* Throw */: {
TRY(builder.append("Token::Throw"sv));
[[maybe_unused]] auto const& that = this->as.Throw;
TRY(builder.appendff("({})", that.value));
break;}
case 99 /* Throws */: {
TRY(builder.append("Token::Throws"sv));
[[maybe_unused]] auto const& that = this->as.Throws;
TRY(builder.appendff("({})", that.value));
break;}
case 100 /* True */: {
TRY(builder.append("Token::True"sv));
[[maybe_unused]] auto const& that = this->as.True;
TRY(builder.appendff("({})", that.value));
break;}
case 101 /* Try */: {
TRY(builder.append("Token::Try"sv));
[[maybe_unused]] auto const& that = this->as.Try;
TRY(builder.appendff("({})", that.value));
break;}
case 102 /* Unsafe */: {
TRY(builder.append("Token::Unsafe"sv));
[[maybe_unused]] auto const& that = this->as.Unsafe;
TRY(builder.appendff("({})", that.value));
break;}
case 103 /* Virtual */: {
TRY(builder.append("Token::Virtual"sv));
[[maybe_unused]] auto const& that = this->as.Virtual;
TRY(builder.appendff("({})", that.value));
break;}
case 104 /* Weak */: {
TRY(builder.append("Token::Weak"sv));
[[maybe_unused]] auto const& that = this->as.Weak;
TRY(builder.appendff("({})", that.value));
break;}
case 105 /* While */: {
TRY(builder.append("Token::While"sv));
[[maybe_unused]] auto const& that = this->as.While;
TRY(builder.appendff("({})", that.value));
break;}
case 106 /* Yield */: {
TRY(builder.append("Token::Yield"sv));
[[maybe_unused]] auto const& that = this->as.Yield;
TRY(builder.appendff("({})", that.value));
break;}
case 107 /* Guard */: {
TRY(builder.append("Token::Guard"sv));
[[maybe_unused]] auto const& that = this->as.Guard;
TRY(builder.appendff("({})", that.value));
break;}
case 108 /* Implements */: {
TRY(builder.append("Token::Implements"sv));
[[maybe_unused]] auto const& that = this->as.Implements;
TRY(builder.appendff("({})", that.value));
break;}
case 109 /* Requires */: {
TRY(builder.append("Token::Requires"sv));
[[maybe_unused]] auto const& that = this->as.Requires;
TRY(builder.appendff("({})", that.value));
break;}
case 110 /* Trait */: {
TRY(builder.append("Token::Trait"sv));
[[maybe_unused]] auto const& that = this->as.Trait;
TRY(builder.appendff("({})", that.value));
break;}
case 111 /* Garbage */: {
TRY(builder.append("Token::Garbage"sv));
[[maybe_unused]] auto const& that = this->as.Garbage;
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("consumed: {}, ", that.consumed));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
}
return builder.to_string();
}
[[nodiscard]] Token Token::SingleQuotedString(DeprecatedString quote, JaktInternal::Optional<DeprecatedString> prefix, utility::Span span){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.SingleQuotedString.quote) (decltype(quote))(move(quote));
new (&__jakt_uninit_enum.as.SingleQuotedString.prefix) (decltype(prefix))(move(prefix));
new (&__jakt_uninit_enum.as.SingleQuotedString.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::QuotedString(DeprecatedString quote, utility::Span span){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.QuotedString.quote) (decltype(quote))(move(quote));
new (&__jakt_uninit_enum.as.QuotedString.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Number(lexer::LiteralPrefix prefix, DeprecatedString number, lexer::LiteralSuffix suffix, utility::Span span){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.as.Number.prefix) (decltype(prefix))(move(prefix));
new (&__jakt_uninit_enum.as.Number.number) (decltype(number))(move(number));
new (&__jakt_uninit_enum.as.Number.suffix) (decltype(suffix))(move(suffix));
new (&__jakt_uninit_enum.as.Number.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Identifier(DeprecatedString name, utility::Span span){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
new (&__jakt_uninit_enum.as.Identifier.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.as.Identifier.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Semicolon(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 5;
new (&__jakt_uninit_enum.as.Semicolon.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Colon(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 6;
new (&__jakt_uninit_enum.as.Colon.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::ColonColon(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 7;
new (&__jakt_uninit_enum.as.ColonColon.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::LParen(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 8;
new (&__jakt_uninit_enum.as.LParen.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::RParen(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 9;
new (&__jakt_uninit_enum.as.RParen.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::LCurly(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 10;
new (&__jakt_uninit_enum.as.LCurly.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::RCurly(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 11;
new (&__jakt_uninit_enum.as.RCurly.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::LSquare(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 12;
new (&__jakt_uninit_enum.as.LSquare.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::RSquare(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 13;
new (&__jakt_uninit_enum.as.RSquare.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::PercentSign(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 14;
new (&__jakt_uninit_enum.as.PercentSign.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Plus(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 15;
new (&__jakt_uninit_enum.as.Plus.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Minus(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 16;
new (&__jakt_uninit_enum.as.Minus.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Equal(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 17;
new (&__jakt_uninit_enum.as.Equal.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::PlusEqual(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 18;
new (&__jakt_uninit_enum.as.PlusEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::PlusPlus(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 19;
new (&__jakt_uninit_enum.as.PlusPlus.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::MinusEqual(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 20;
new (&__jakt_uninit_enum.as.MinusEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::MinusMinus(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 21;
new (&__jakt_uninit_enum.as.MinusMinus.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::AsteriskEqual(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 22;
new (&__jakt_uninit_enum.as.AsteriskEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::ForwardSlashEqual(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 23;
new (&__jakt_uninit_enum.as.ForwardSlashEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::PercentSignEqual(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 24;
new (&__jakt_uninit_enum.as.PercentSignEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::NotEqual(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 25;
new (&__jakt_uninit_enum.as.NotEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::DoubleEqual(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 26;
new (&__jakt_uninit_enum.as.DoubleEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::GreaterThan(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 27;
new (&__jakt_uninit_enum.as.GreaterThan.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::GreaterThanOrEqual(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 28;
new (&__jakt_uninit_enum.as.GreaterThanOrEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::LessThan(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 29;
new (&__jakt_uninit_enum.as.LessThan.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::LessThanOrEqual(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 30;
new (&__jakt_uninit_enum.as.LessThanOrEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::LeftArithmeticShift(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 31;
new (&__jakt_uninit_enum.as.LeftArithmeticShift.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::LeftShift(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 32;
new (&__jakt_uninit_enum.as.LeftShift.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::LeftShiftEqual(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 33;
new (&__jakt_uninit_enum.as.LeftShiftEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::RightShift(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 34;
new (&__jakt_uninit_enum.as.RightShift.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::RightArithmeticShift(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 35;
new (&__jakt_uninit_enum.as.RightArithmeticShift.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::RightShiftEqual(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 36;
new (&__jakt_uninit_enum.as.RightShiftEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Asterisk(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 37;
new (&__jakt_uninit_enum.as.Asterisk.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Ampersand(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 38;
new (&__jakt_uninit_enum.as.Ampersand.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::AmpersandEqual(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 39;
new (&__jakt_uninit_enum.as.AmpersandEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::AmpersandAmpersand(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 40;
new (&__jakt_uninit_enum.as.AmpersandAmpersand.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Pipe(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 41;
new (&__jakt_uninit_enum.as.Pipe.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::PipeEqual(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 42;
new (&__jakt_uninit_enum.as.PipeEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::PipePipe(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 43;
new (&__jakt_uninit_enum.as.PipePipe.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Caret(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 44;
new (&__jakt_uninit_enum.as.Caret.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::CaretEqual(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 45;
new (&__jakt_uninit_enum.as.CaretEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Dollar(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 46;
new (&__jakt_uninit_enum.as.Dollar.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Tilde(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 47;
new (&__jakt_uninit_enum.as.Tilde.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::ForwardSlash(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 48;
new (&__jakt_uninit_enum.as.ForwardSlash.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::ExclamationPoint(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 49;
new (&__jakt_uninit_enum.as.ExclamationPoint.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::QuestionMark(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 50;
new (&__jakt_uninit_enum.as.QuestionMark.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::QuestionMarkQuestionMark(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 51;
new (&__jakt_uninit_enum.as.QuestionMarkQuestionMark.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::QuestionMarkQuestionMarkEqual(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 52;
new (&__jakt_uninit_enum.as.QuestionMarkQuestionMarkEqual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Comma(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 53;
new (&__jakt_uninit_enum.as.Comma.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Dot(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 54;
new (&__jakt_uninit_enum.as.Dot.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::DotDot(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 55;
new (&__jakt_uninit_enum.as.DotDot.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Eol(JaktInternal::Optional<DeprecatedString> comment, utility::Span span){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 56;
new (&__jakt_uninit_enum.as.Eol.comment) (decltype(comment))(move(comment));
new (&__jakt_uninit_enum.as.Eol.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Eof(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 57;
new (&__jakt_uninit_enum.as.Eof.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::FatArrow(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 58;
new (&__jakt_uninit_enum.as.FatArrow.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Arrow(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 59;
new (&__jakt_uninit_enum.as.Arrow.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::And(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 60;
new (&__jakt_uninit_enum.as.And.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Anon(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 61;
new (&__jakt_uninit_enum.as.Anon.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::As(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 62;
new (&__jakt_uninit_enum.as.As.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Boxed(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 63;
new (&__jakt_uninit_enum.as.Boxed.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Break(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 64;
new (&__jakt_uninit_enum.as.Break.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Catch(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 65;
new (&__jakt_uninit_enum.as.Catch.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Class(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 66;
new (&__jakt_uninit_enum.as.Class.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Continue(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 67;
new (&__jakt_uninit_enum.as.Continue.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Cpp(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 68;
new (&__jakt_uninit_enum.as.Cpp.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Defer(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 69;
new (&__jakt_uninit_enum.as.Defer.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Destructor(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 70;
new (&__jakt_uninit_enum.as.Destructor.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Else(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 71;
new (&__jakt_uninit_enum.as.Else.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Enum(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 72;
new (&__jakt_uninit_enum.as.Enum.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Extern(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 73;
new (&__jakt_uninit_enum.as.Extern.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::False(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 74;
new (&__jakt_uninit_enum.as.False.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::For(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 75;
new (&__jakt_uninit_enum.as.For.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Fn(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 76;
new (&__jakt_uninit_enum.as.Fn.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Comptime(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 77;
new (&__jakt_uninit_enum.as.Comptime.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::If(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 78;
new (&__jakt_uninit_enum.as.If.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Import(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 79;
new (&__jakt_uninit_enum.as.Import.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::In(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 80;
new (&__jakt_uninit_enum.as.In.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Is(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 81;
new (&__jakt_uninit_enum.as.Is.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Let(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 82;
new (&__jakt_uninit_enum.as.Let.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Loop(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 83;
new (&__jakt_uninit_enum.as.Loop.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Match(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 84;
new (&__jakt_uninit_enum.as.Match.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Mut(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 85;
new (&__jakt_uninit_enum.as.Mut.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Namespace(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 86;
new (&__jakt_uninit_enum.as.Namespace.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Not(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 87;
new (&__jakt_uninit_enum.as.Not.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Or(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 88;
new (&__jakt_uninit_enum.as.Or.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Override(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 89;
new (&__jakt_uninit_enum.as.Override.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Private(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 90;
new (&__jakt_uninit_enum.as.Private.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Public(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 91;
new (&__jakt_uninit_enum.as.Public.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Raw(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 92;
new (&__jakt_uninit_enum.as.Raw.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Reflect(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 93;
new (&__jakt_uninit_enum.as.Reflect.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Return(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 94;
new (&__jakt_uninit_enum.as.Return.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Restricted(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 95;
new (&__jakt_uninit_enum.as.Restricted.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Sizeof(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 96;
new (&__jakt_uninit_enum.as.Sizeof.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Struct(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 97;
new (&__jakt_uninit_enum.as.Struct.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::This(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 98;
new (&__jakt_uninit_enum.as.This.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Throw(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 99;
new (&__jakt_uninit_enum.as.Throw.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Throws(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 100;
new (&__jakt_uninit_enum.as.Throws.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::True(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 101;
new (&__jakt_uninit_enum.as.True.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Try(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 102;
new (&__jakt_uninit_enum.as.Try.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Unsafe(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 103;
new (&__jakt_uninit_enum.as.Unsafe.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Virtual(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 104;
new (&__jakt_uninit_enum.as.Virtual.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Weak(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 105;
new (&__jakt_uninit_enum.as.Weak.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::While(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 106;
new (&__jakt_uninit_enum.as.While.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Yield(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 107;
new (&__jakt_uninit_enum.as.Yield.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Guard(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 108;
new (&__jakt_uninit_enum.as.Guard.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Implements(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 109;
new (&__jakt_uninit_enum.as.Implements.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Requires(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 110;
new (&__jakt_uninit_enum.as.Requires.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Trait(utility::Span value){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 111;
new (&__jakt_uninit_enum.as.Trait.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Token Token::Garbage(JaktInternal::Optional<DeprecatedString> consumed, utility::Span span){
Token __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 112;
new (&__jakt_uninit_enum.as.Garbage.consumed) (decltype(consumed))(move(consumed));
new (&__jakt_uninit_enum.as.Garbage.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
Token& Token::operator=(Token const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* SingleQuotedString */:
new (&this->as.SingleQuotedString.quote) (decltype(this->as.SingleQuotedString.quote))(rhs.as.SingleQuotedString.quote);
new (&this->as.SingleQuotedString.prefix) (decltype(this->as.SingleQuotedString.prefix))(rhs.as.SingleQuotedString.prefix);
new (&this->as.SingleQuotedString.span) (decltype(this->as.SingleQuotedString.span))(rhs.as.SingleQuotedString.span);
break;
case 1 /* QuotedString */:
new (&this->as.QuotedString.quote) (decltype(this->as.QuotedString.quote))(rhs.as.QuotedString.quote);
new (&this->as.QuotedString.span) (decltype(this->as.QuotedString.span))(rhs.as.QuotedString.span);
break;
case 2 /* Number */:
new (&this->as.Number.prefix) (decltype(this->as.Number.prefix))(rhs.as.Number.prefix);
new (&this->as.Number.number) (decltype(this->as.Number.number))(rhs.as.Number.number);
new (&this->as.Number.suffix) (decltype(this->as.Number.suffix))(rhs.as.Number.suffix);
new (&this->as.Number.span) (decltype(this->as.Number.span))(rhs.as.Number.span);
break;
case 3 /* Identifier */:
new (&this->as.Identifier.name) (decltype(this->as.Identifier.name))(rhs.as.Identifier.name);
new (&this->as.Identifier.span) (decltype(this->as.Identifier.span))(rhs.as.Identifier.span);
break;
case 4 /* Semicolon */:
new (&this->as.Semicolon.value) (decltype(this->as.Semicolon.value))(rhs.as.Semicolon.value);
break;
case 5 /* Colon */:
new (&this->as.Colon.value) (decltype(this->as.Colon.value))(rhs.as.Colon.value);
break;
case 6 /* ColonColon */:
new (&this->as.ColonColon.value) (decltype(this->as.ColonColon.value))(rhs.as.ColonColon.value);
break;
case 7 /* LParen */:
new (&this->as.LParen.value) (decltype(this->as.LParen.value))(rhs.as.LParen.value);
break;
case 8 /* RParen */:
new (&this->as.RParen.value) (decltype(this->as.RParen.value))(rhs.as.RParen.value);
break;
case 9 /* LCurly */:
new (&this->as.LCurly.value) (decltype(this->as.LCurly.value))(rhs.as.LCurly.value);
break;
case 10 /* RCurly */:
new (&this->as.RCurly.value) (decltype(this->as.RCurly.value))(rhs.as.RCurly.value);
break;
case 11 /* LSquare */:
new (&this->as.LSquare.value) (decltype(this->as.LSquare.value))(rhs.as.LSquare.value);
break;
case 12 /* RSquare */:
new (&this->as.RSquare.value) (decltype(this->as.RSquare.value))(rhs.as.RSquare.value);
break;
case 13 /* PercentSign */:
new (&this->as.PercentSign.value) (decltype(this->as.PercentSign.value))(rhs.as.PercentSign.value);
break;
case 14 /* Plus */:
new (&this->as.Plus.value) (decltype(this->as.Plus.value))(rhs.as.Plus.value);
break;
case 15 /* Minus */:
new (&this->as.Minus.value) (decltype(this->as.Minus.value))(rhs.as.Minus.value);
break;
case 16 /* Equal */:
new (&this->as.Equal.value) (decltype(this->as.Equal.value))(rhs.as.Equal.value);
break;
case 17 /* PlusEqual */:
new (&this->as.PlusEqual.value) (decltype(this->as.PlusEqual.value))(rhs.as.PlusEqual.value);
break;
case 18 /* PlusPlus */:
new (&this->as.PlusPlus.value) (decltype(this->as.PlusPlus.value))(rhs.as.PlusPlus.value);
break;
case 19 /* MinusEqual */:
new (&this->as.MinusEqual.value) (decltype(this->as.MinusEqual.value))(rhs.as.MinusEqual.value);
break;
case 20 /* MinusMinus */:
new (&this->as.MinusMinus.value) (decltype(this->as.MinusMinus.value))(rhs.as.MinusMinus.value);
break;
case 21 /* AsteriskEqual */:
new (&this->as.AsteriskEqual.value) (decltype(this->as.AsteriskEqual.value))(rhs.as.AsteriskEqual.value);
break;
case 22 /* ForwardSlashEqual */:
new (&this->as.ForwardSlashEqual.value) (decltype(this->as.ForwardSlashEqual.value))(rhs.as.ForwardSlashEqual.value);
break;
case 23 /* PercentSignEqual */:
new (&this->as.PercentSignEqual.value) (decltype(this->as.PercentSignEqual.value))(rhs.as.PercentSignEqual.value);
break;
case 24 /* NotEqual */:
new (&this->as.NotEqual.value) (decltype(this->as.NotEqual.value))(rhs.as.NotEqual.value);
break;
case 25 /* DoubleEqual */:
new (&this->as.DoubleEqual.value) (decltype(this->as.DoubleEqual.value))(rhs.as.DoubleEqual.value);
break;
case 26 /* GreaterThan */:
new (&this->as.GreaterThan.value) (decltype(this->as.GreaterThan.value))(rhs.as.GreaterThan.value);
break;
case 27 /* GreaterThanOrEqual */:
new (&this->as.GreaterThanOrEqual.value) (decltype(this->as.GreaterThanOrEqual.value))(rhs.as.GreaterThanOrEqual.value);
break;
case 28 /* LessThan */:
new (&this->as.LessThan.value) (decltype(this->as.LessThan.value))(rhs.as.LessThan.value);
break;
case 29 /* LessThanOrEqual */:
new (&this->as.LessThanOrEqual.value) (decltype(this->as.LessThanOrEqual.value))(rhs.as.LessThanOrEqual.value);
break;
case 30 /* LeftArithmeticShift */:
new (&this->as.LeftArithmeticShift.value) (decltype(this->as.LeftArithmeticShift.value))(rhs.as.LeftArithmeticShift.value);
break;
case 31 /* LeftShift */:
new (&this->as.LeftShift.value) (decltype(this->as.LeftShift.value))(rhs.as.LeftShift.value);
break;
case 32 /* LeftShiftEqual */:
new (&this->as.LeftShiftEqual.value) (decltype(this->as.LeftShiftEqual.value))(rhs.as.LeftShiftEqual.value);
break;
case 33 /* RightShift */:
new (&this->as.RightShift.value) (decltype(this->as.RightShift.value))(rhs.as.RightShift.value);
break;
case 34 /* RightArithmeticShift */:
new (&this->as.RightArithmeticShift.value) (decltype(this->as.RightArithmeticShift.value))(rhs.as.RightArithmeticShift.value);
break;
case 35 /* RightShiftEqual */:
new (&this->as.RightShiftEqual.value) (decltype(this->as.RightShiftEqual.value))(rhs.as.RightShiftEqual.value);
break;
case 36 /* Asterisk */:
new (&this->as.Asterisk.value) (decltype(this->as.Asterisk.value))(rhs.as.Asterisk.value);
break;
case 37 /* Ampersand */:
new (&this->as.Ampersand.value) (decltype(this->as.Ampersand.value))(rhs.as.Ampersand.value);
break;
case 38 /* AmpersandEqual */:
new (&this->as.AmpersandEqual.value) (decltype(this->as.AmpersandEqual.value))(rhs.as.AmpersandEqual.value);
break;
case 39 /* AmpersandAmpersand */:
new (&this->as.AmpersandAmpersand.value) (decltype(this->as.AmpersandAmpersand.value))(rhs.as.AmpersandAmpersand.value);
break;
case 40 /* Pipe */:
new (&this->as.Pipe.value) (decltype(this->as.Pipe.value))(rhs.as.Pipe.value);
break;
case 41 /* PipeEqual */:
new (&this->as.PipeEqual.value) (decltype(this->as.PipeEqual.value))(rhs.as.PipeEqual.value);
break;
case 42 /* PipePipe */:
new (&this->as.PipePipe.value) (decltype(this->as.PipePipe.value))(rhs.as.PipePipe.value);
break;
case 43 /* Caret */:
new (&this->as.Caret.value) (decltype(this->as.Caret.value))(rhs.as.Caret.value);
break;
case 44 /* CaretEqual */:
new (&this->as.CaretEqual.value) (decltype(this->as.CaretEqual.value))(rhs.as.CaretEqual.value);
break;
case 45 /* Dollar */:
new (&this->as.Dollar.value) (decltype(this->as.Dollar.value))(rhs.as.Dollar.value);
break;
case 46 /* Tilde */:
new (&this->as.Tilde.value) (decltype(this->as.Tilde.value))(rhs.as.Tilde.value);
break;
case 47 /* ForwardSlash */:
new (&this->as.ForwardSlash.value) (decltype(this->as.ForwardSlash.value))(rhs.as.ForwardSlash.value);
break;
case 48 /* ExclamationPoint */:
new (&this->as.ExclamationPoint.value) (decltype(this->as.ExclamationPoint.value))(rhs.as.ExclamationPoint.value);
break;
case 49 /* QuestionMark */:
new (&this->as.QuestionMark.value) (decltype(this->as.QuestionMark.value))(rhs.as.QuestionMark.value);
break;
case 50 /* QuestionMarkQuestionMark */:
new (&this->as.QuestionMarkQuestionMark.value) (decltype(this->as.QuestionMarkQuestionMark.value))(rhs.as.QuestionMarkQuestionMark.value);
break;
case 51 /* QuestionMarkQuestionMarkEqual */:
new (&this->as.QuestionMarkQuestionMarkEqual.value) (decltype(this->as.QuestionMarkQuestionMarkEqual.value))(rhs.as.QuestionMarkQuestionMarkEqual.value);
break;
case 52 /* Comma */:
new (&this->as.Comma.value) (decltype(this->as.Comma.value))(rhs.as.Comma.value);
break;
case 53 /* Dot */:
new (&this->as.Dot.value) (decltype(this->as.Dot.value))(rhs.as.Dot.value);
break;
case 54 /* DotDot */:
new (&this->as.DotDot.value) (decltype(this->as.DotDot.value))(rhs.as.DotDot.value);
break;
case 55 /* Eol */:
new (&this->as.Eol.comment) (decltype(this->as.Eol.comment))(rhs.as.Eol.comment);
new (&this->as.Eol.span) (decltype(this->as.Eol.span))(rhs.as.Eol.span);
break;
case 56 /* Eof */:
new (&this->as.Eof.value) (decltype(this->as.Eof.value))(rhs.as.Eof.value);
break;
case 57 /* FatArrow */:
new (&this->as.FatArrow.value) (decltype(this->as.FatArrow.value))(rhs.as.FatArrow.value);
break;
case 58 /* Arrow */:
new (&this->as.Arrow.value) (decltype(this->as.Arrow.value))(rhs.as.Arrow.value);
break;
case 59 /* And */:
new (&this->as.And.value) (decltype(this->as.And.value))(rhs.as.And.value);
break;
case 60 /* Anon */:
new (&this->as.Anon.value) (decltype(this->as.Anon.value))(rhs.as.Anon.value);
break;
case 61 /* As */:
new (&this->as.As.value) (decltype(this->as.As.value))(rhs.as.As.value);
break;
case 62 /* Boxed */:
new (&this->as.Boxed.value) (decltype(this->as.Boxed.value))(rhs.as.Boxed.value);
break;
case 63 /* Break */:
new (&this->as.Break.value) (decltype(this->as.Break.value))(rhs.as.Break.value);
break;
case 64 /* Catch */:
new (&this->as.Catch.value) (decltype(this->as.Catch.value))(rhs.as.Catch.value);
break;
case 65 /* Class */:
new (&this->as.Class.value) (decltype(this->as.Class.value))(rhs.as.Class.value);
break;
case 66 /* Continue */:
new (&this->as.Continue.value) (decltype(this->as.Continue.value))(rhs.as.Continue.value);
break;
case 67 /* Cpp */:
new (&this->as.Cpp.value) (decltype(this->as.Cpp.value))(rhs.as.Cpp.value);
break;
case 68 /* Defer */:
new (&this->as.Defer.value) (decltype(this->as.Defer.value))(rhs.as.Defer.value);
break;
case 69 /* Destructor */:
new (&this->as.Destructor.value) (decltype(this->as.Destructor.value))(rhs.as.Destructor.value);
break;
case 70 /* Else */:
new (&this->as.Else.value) (decltype(this->as.Else.value))(rhs.as.Else.value);
break;
case 71 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(rhs.as.Enum.value);
break;
case 72 /* Extern */:
new (&this->as.Extern.value) (decltype(this->as.Extern.value))(rhs.as.Extern.value);
break;
case 73 /* False */:
new (&this->as.False.value) (decltype(this->as.False.value))(rhs.as.False.value);
break;
case 74 /* For */:
new (&this->as.For.value) (decltype(this->as.For.value))(rhs.as.For.value);
break;
case 75 /* Fn */:
new (&this->as.Fn.value) (decltype(this->as.Fn.value))(rhs.as.Fn.value);
break;
case 76 /* Comptime */:
new (&this->as.Comptime.value) (decltype(this->as.Comptime.value))(rhs.as.Comptime.value);
break;
case 77 /* If */:
new (&this->as.If.value) (decltype(this->as.If.value))(rhs.as.If.value);
break;
case 78 /* Import */:
new (&this->as.Import.value) (decltype(this->as.Import.value))(rhs.as.Import.value);
break;
case 79 /* In */:
new (&this->as.In.value) (decltype(this->as.In.value))(rhs.as.In.value);
break;
case 80 /* Is */:
new (&this->as.Is.value) (decltype(this->as.Is.value))(rhs.as.Is.value);
break;
case 81 /* Let */:
new (&this->as.Let.value) (decltype(this->as.Let.value))(rhs.as.Let.value);
break;
case 82 /* Loop */:
new (&this->as.Loop.value) (decltype(this->as.Loop.value))(rhs.as.Loop.value);
break;
case 83 /* Match */:
new (&this->as.Match.value) (decltype(this->as.Match.value))(rhs.as.Match.value);
break;
case 84 /* Mut */:
new (&this->as.Mut.value) (decltype(this->as.Mut.value))(rhs.as.Mut.value);
break;
case 85 /* Namespace */:
new (&this->as.Namespace.value) (decltype(this->as.Namespace.value))(rhs.as.Namespace.value);
break;
case 86 /* Not */:
new (&this->as.Not.value) (decltype(this->as.Not.value))(rhs.as.Not.value);
break;
case 87 /* Or */:
new (&this->as.Or.value) (decltype(this->as.Or.value))(rhs.as.Or.value);
break;
case 88 /* Override */:
new (&this->as.Override.value) (decltype(this->as.Override.value))(rhs.as.Override.value);
break;
case 89 /* Private */:
new (&this->as.Private.value) (decltype(this->as.Private.value))(rhs.as.Private.value);
break;
case 90 /* Public */:
new (&this->as.Public.value) (decltype(this->as.Public.value))(rhs.as.Public.value);
break;
case 91 /* Raw */:
new (&this->as.Raw.value) (decltype(this->as.Raw.value))(rhs.as.Raw.value);
break;
case 92 /* Reflect */:
new (&this->as.Reflect.value) (decltype(this->as.Reflect.value))(rhs.as.Reflect.value);
break;
case 93 /* Return */:
new (&this->as.Return.value) (decltype(this->as.Return.value))(rhs.as.Return.value);
break;
case 94 /* Restricted */:
new (&this->as.Restricted.value) (decltype(this->as.Restricted.value))(rhs.as.Restricted.value);
break;
case 95 /* Sizeof */:
new (&this->as.Sizeof.value) (decltype(this->as.Sizeof.value))(rhs.as.Sizeof.value);
break;
case 96 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(rhs.as.Struct.value);
break;
case 97 /* This */:
new (&this->as.This.value) (decltype(this->as.This.value))(rhs.as.This.value);
break;
case 98 /* Throw */:
new (&this->as.Throw.value) (decltype(this->as.Throw.value))(rhs.as.Throw.value);
break;
case 99 /* Throws */:
new (&this->as.Throws.value) (decltype(this->as.Throws.value))(rhs.as.Throws.value);
break;
case 100 /* True */:
new (&this->as.True.value) (decltype(this->as.True.value))(rhs.as.True.value);
break;
case 101 /* Try */:
new (&this->as.Try.value) (decltype(this->as.Try.value))(rhs.as.Try.value);
break;
case 102 /* Unsafe */:
new (&this->as.Unsafe.value) (decltype(this->as.Unsafe.value))(rhs.as.Unsafe.value);
break;
case 103 /* Virtual */:
new (&this->as.Virtual.value) (decltype(this->as.Virtual.value))(rhs.as.Virtual.value);
break;
case 104 /* Weak */:
new (&this->as.Weak.value) (decltype(this->as.Weak.value))(rhs.as.Weak.value);
break;
case 105 /* While */:
new (&this->as.While.value) (decltype(this->as.While.value))(rhs.as.While.value);
break;
case 106 /* Yield */:
new (&this->as.Yield.value) (decltype(this->as.Yield.value))(rhs.as.Yield.value);
break;
case 107 /* Guard */:
new (&this->as.Guard.value) (decltype(this->as.Guard.value))(rhs.as.Guard.value);
break;
case 108 /* Implements */:
new (&this->as.Implements.value) (decltype(this->as.Implements.value))(rhs.as.Implements.value);
break;
case 109 /* Requires */:
new (&this->as.Requires.value) (decltype(this->as.Requires.value))(rhs.as.Requires.value);
break;
case 110 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(rhs.as.Trait.value);
break;
case 111 /* Garbage */:
new (&this->as.Garbage.consumed) (decltype(this->as.Garbage.consumed))(rhs.as.Garbage.consumed);
new (&this->as.Garbage.span) (decltype(this->as.Garbage.span))(rhs.as.Garbage.span);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* SingleQuotedString */:
this->as.SingleQuotedString.quote = rhs.as.SingleQuotedString.quote;
this->as.SingleQuotedString.prefix = rhs.as.SingleQuotedString.prefix;
this->as.SingleQuotedString.span = rhs.as.SingleQuotedString.span;
break;
case 1 /* QuotedString */:
this->as.QuotedString.quote = rhs.as.QuotedString.quote;
this->as.QuotedString.span = rhs.as.QuotedString.span;
break;
case 2 /* Number */:
this->as.Number.prefix = rhs.as.Number.prefix;
this->as.Number.number = rhs.as.Number.number;
this->as.Number.suffix = rhs.as.Number.suffix;
this->as.Number.span = rhs.as.Number.span;
break;
case 3 /* Identifier */:
this->as.Identifier.name = rhs.as.Identifier.name;
this->as.Identifier.span = rhs.as.Identifier.span;
break;
case 4 /* Semicolon */:
this->as.Semicolon.value = rhs.as.Semicolon.value;
break;
case 5 /* Colon */:
this->as.Colon.value = rhs.as.Colon.value;
break;
case 6 /* ColonColon */:
this->as.ColonColon.value = rhs.as.ColonColon.value;
break;
case 7 /* LParen */:
this->as.LParen.value = rhs.as.LParen.value;
break;
case 8 /* RParen */:
this->as.RParen.value = rhs.as.RParen.value;
break;
case 9 /* LCurly */:
this->as.LCurly.value = rhs.as.LCurly.value;
break;
case 10 /* RCurly */:
this->as.RCurly.value = rhs.as.RCurly.value;
break;
case 11 /* LSquare */:
this->as.LSquare.value = rhs.as.LSquare.value;
break;
case 12 /* RSquare */:
this->as.RSquare.value = rhs.as.RSquare.value;
break;
case 13 /* PercentSign */:
this->as.PercentSign.value = rhs.as.PercentSign.value;
break;
case 14 /* Plus */:
this->as.Plus.value = rhs.as.Plus.value;
break;
case 15 /* Minus */:
this->as.Minus.value = rhs.as.Minus.value;
break;
case 16 /* Equal */:
this->as.Equal.value = rhs.as.Equal.value;
break;
case 17 /* PlusEqual */:
this->as.PlusEqual.value = rhs.as.PlusEqual.value;
break;
case 18 /* PlusPlus */:
this->as.PlusPlus.value = rhs.as.PlusPlus.value;
break;
case 19 /* MinusEqual */:
this->as.MinusEqual.value = rhs.as.MinusEqual.value;
break;
case 20 /* MinusMinus */:
this->as.MinusMinus.value = rhs.as.MinusMinus.value;
break;
case 21 /* AsteriskEqual */:
this->as.AsteriskEqual.value = rhs.as.AsteriskEqual.value;
break;
case 22 /* ForwardSlashEqual */:
this->as.ForwardSlashEqual.value = rhs.as.ForwardSlashEqual.value;
break;
case 23 /* PercentSignEqual */:
this->as.PercentSignEqual.value = rhs.as.PercentSignEqual.value;
break;
case 24 /* NotEqual */:
this->as.NotEqual.value = rhs.as.NotEqual.value;
break;
case 25 /* DoubleEqual */:
this->as.DoubleEqual.value = rhs.as.DoubleEqual.value;
break;
case 26 /* GreaterThan */:
this->as.GreaterThan.value = rhs.as.GreaterThan.value;
break;
case 27 /* GreaterThanOrEqual */:
this->as.GreaterThanOrEqual.value = rhs.as.GreaterThanOrEqual.value;
break;
case 28 /* LessThan */:
this->as.LessThan.value = rhs.as.LessThan.value;
break;
case 29 /* LessThanOrEqual */:
this->as.LessThanOrEqual.value = rhs.as.LessThanOrEqual.value;
break;
case 30 /* LeftArithmeticShift */:
this->as.LeftArithmeticShift.value = rhs.as.LeftArithmeticShift.value;
break;
case 31 /* LeftShift */:
this->as.LeftShift.value = rhs.as.LeftShift.value;
break;
case 32 /* LeftShiftEqual */:
this->as.LeftShiftEqual.value = rhs.as.LeftShiftEqual.value;
break;
case 33 /* RightShift */:
this->as.RightShift.value = rhs.as.RightShift.value;
break;
case 34 /* RightArithmeticShift */:
this->as.RightArithmeticShift.value = rhs.as.RightArithmeticShift.value;
break;
case 35 /* RightShiftEqual */:
this->as.RightShiftEqual.value = rhs.as.RightShiftEqual.value;
break;
case 36 /* Asterisk */:
this->as.Asterisk.value = rhs.as.Asterisk.value;
break;
case 37 /* Ampersand */:
this->as.Ampersand.value = rhs.as.Ampersand.value;
break;
case 38 /* AmpersandEqual */:
this->as.AmpersandEqual.value = rhs.as.AmpersandEqual.value;
break;
case 39 /* AmpersandAmpersand */:
this->as.AmpersandAmpersand.value = rhs.as.AmpersandAmpersand.value;
break;
case 40 /* Pipe */:
this->as.Pipe.value = rhs.as.Pipe.value;
break;
case 41 /* PipeEqual */:
this->as.PipeEqual.value = rhs.as.PipeEqual.value;
break;
case 42 /* PipePipe */:
this->as.PipePipe.value = rhs.as.PipePipe.value;
break;
case 43 /* Caret */:
this->as.Caret.value = rhs.as.Caret.value;
break;
case 44 /* CaretEqual */:
this->as.CaretEqual.value = rhs.as.CaretEqual.value;
break;
case 45 /* Dollar */:
this->as.Dollar.value = rhs.as.Dollar.value;
break;
case 46 /* Tilde */:
this->as.Tilde.value = rhs.as.Tilde.value;
break;
case 47 /* ForwardSlash */:
this->as.ForwardSlash.value = rhs.as.ForwardSlash.value;
break;
case 48 /* ExclamationPoint */:
this->as.ExclamationPoint.value = rhs.as.ExclamationPoint.value;
break;
case 49 /* QuestionMark */:
this->as.QuestionMark.value = rhs.as.QuestionMark.value;
break;
case 50 /* QuestionMarkQuestionMark */:
this->as.QuestionMarkQuestionMark.value = rhs.as.QuestionMarkQuestionMark.value;
break;
case 51 /* QuestionMarkQuestionMarkEqual */:
this->as.QuestionMarkQuestionMarkEqual.value = rhs.as.QuestionMarkQuestionMarkEqual.value;
break;
case 52 /* Comma */:
this->as.Comma.value = rhs.as.Comma.value;
break;
case 53 /* Dot */:
this->as.Dot.value = rhs.as.Dot.value;
break;
case 54 /* DotDot */:
this->as.DotDot.value = rhs.as.DotDot.value;
break;
case 55 /* Eol */:
this->as.Eol.comment = rhs.as.Eol.comment;
this->as.Eol.span = rhs.as.Eol.span;
break;
case 56 /* Eof */:
this->as.Eof.value = rhs.as.Eof.value;
break;
case 57 /* FatArrow */:
this->as.FatArrow.value = rhs.as.FatArrow.value;
break;
case 58 /* Arrow */:
this->as.Arrow.value = rhs.as.Arrow.value;
break;
case 59 /* And */:
this->as.And.value = rhs.as.And.value;
break;
case 60 /* Anon */:
this->as.Anon.value = rhs.as.Anon.value;
break;
case 61 /* As */:
this->as.As.value = rhs.as.As.value;
break;
case 62 /* Boxed */:
this->as.Boxed.value = rhs.as.Boxed.value;
break;
case 63 /* Break */:
this->as.Break.value = rhs.as.Break.value;
break;
case 64 /* Catch */:
this->as.Catch.value = rhs.as.Catch.value;
break;
case 65 /* Class */:
this->as.Class.value = rhs.as.Class.value;
break;
case 66 /* Continue */:
this->as.Continue.value = rhs.as.Continue.value;
break;
case 67 /* Cpp */:
this->as.Cpp.value = rhs.as.Cpp.value;
break;
case 68 /* Defer */:
this->as.Defer.value = rhs.as.Defer.value;
break;
case 69 /* Destructor */:
this->as.Destructor.value = rhs.as.Destructor.value;
break;
case 70 /* Else */:
this->as.Else.value = rhs.as.Else.value;
break;
case 71 /* Enum */:
this->as.Enum.value = rhs.as.Enum.value;
break;
case 72 /* Extern */:
this->as.Extern.value = rhs.as.Extern.value;
break;
case 73 /* False */:
this->as.False.value = rhs.as.False.value;
break;
case 74 /* For */:
this->as.For.value = rhs.as.For.value;
break;
case 75 /* Fn */:
this->as.Fn.value = rhs.as.Fn.value;
break;
case 76 /* Comptime */:
this->as.Comptime.value = rhs.as.Comptime.value;
break;
case 77 /* If */:
this->as.If.value = rhs.as.If.value;
break;
case 78 /* Import */:
this->as.Import.value = rhs.as.Import.value;
break;
case 79 /* In */:
this->as.In.value = rhs.as.In.value;
break;
case 80 /* Is */:
this->as.Is.value = rhs.as.Is.value;
break;
case 81 /* Let */:
this->as.Let.value = rhs.as.Let.value;
break;
case 82 /* Loop */:
this->as.Loop.value = rhs.as.Loop.value;
break;
case 83 /* Match */:
this->as.Match.value = rhs.as.Match.value;
break;
case 84 /* Mut */:
this->as.Mut.value = rhs.as.Mut.value;
break;
case 85 /* Namespace */:
this->as.Namespace.value = rhs.as.Namespace.value;
break;
case 86 /* Not */:
this->as.Not.value = rhs.as.Not.value;
break;
case 87 /* Or */:
this->as.Or.value = rhs.as.Or.value;
break;
case 88 /* Override */:
this->as.Override.value = rhs.as.Override.value;
break;
case 89 /* Private */:
this->as.Private.value = rhs.as.Private.value;
break;
case 90 /* Public */:
this->as.Public.value = rhs.as.Public.value;
break;
case 91 /* Raw */:
this->as.Raw.value = rhs.as.Raw.value;
break;
case 92 /* Reflect */:
this->as.Reflect.value = rhs.as.Reflect.value;
break;
case 93 /* Return */:
this->as.Return.value = rhs.as.Return.value;
break;
case 94 /* Restricted */:
this->as.Restricted.value = rhs.as.Restricted.value;
break;
case 95 /* Sizeof */:
this->as.Sizeof.value = rhs.as.Sizeof.value;
break;
case 96 /* Struct */:
this->as.Struct.value = rhs.as.Struct.value;
break;
case 97 /* This */:
this->as.This.value = rhs.as.This.value;
break;
case 98 /* Throw */:
this->as.Throw.value = rhs.as.Throw.value;
break;
case 99 /* Throws */:
this->as.Throws.value = rhs.as.Throws.value;
break;
case 100 /* True */:
this->as.True.value = rhs.as.True.value;
break;
case 101 /* Try */:
this->as.Try.value = rhs.as.Try.value;
break;
case 102 /* Unsafe */:
this->as.Unsafe.value = rhs.as.Unsafe.value;
break;
case 103 /* Virtual */:
this->as.Virtual.value = rhs.as.Virtual.value;
break;
case 104 /* Weak */:
this->as.Weak.value = rhs.as.Weak.value;
break;
case 105 /* While */:
this->as.While.value = rhs.as.While.value;
break;
case 106 /* Yield */:
this->as.Yield.value = rhs.as.Yield.value;
break;
case 107 /* Guard */:
this->as.Guard.value = rhs.as.Guard.value;
break;
case 108 /* Implements */:
this->as.Implements.value = rhs.as.Implements.value;
break;
case 109 /* Requires */:
this->as.Requires.value = rhs.as.Requires.value;
break;
case 110 /* Trait */:
this->as.Trait.value = rhs.as.Trait.value;
break;
case 111 /* Garbage */:
this->as.Garbage.consumed = rhs.as.Garbage.consumed;
this->as.Garbage.span = rhs.as.Garbage.span;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
Token::Token(Token const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* SingleQuotedString */:
new (&this->as.SingleQuotedString.quote) (decltype(this->as.SingleQuotedString.quote))(rhs.as.SingleQuotedString.quote);
new (&this->as.SingleQuotedString.prefix) (decltype(this->as.SingleQuotedString.prefix))(rhs.as.SingleQuotedString.prefix);
new (&this->as.SingleQuotedString.span) (decltype(this->as.SingleQuotedString.span))(rhs.as.SingleQuotedString.span);
break;
case 1 /* QuotedString */:
new (&this->as.QuotedString.quote) (decltype(this->as.QuotedString.quote))(rhs.as.QuotedString.quote);
new (&this->as.QuotedString.span) (decltype(this->as.QuotedString.span))(rhs.as.QuotedString.span);
break;
case 2 /* Number */:
new (&this->as.Number.prefix) (decltype(this->as.Number.prefix))(rhs.as.Number.prefix);
new (&this->as.Number.number) (decltype(this->as.Number.number))(rhs.as.Number.number);
new (&this->as.Number.suffix) (decltype(this->as.Number.suffix))(rhs.as.Number.suffix);
new (&this->as.Number.span) (decltype(this->as.Number.span))(rhs.as.Number.span);
break;
case 3 /* Identifier */:
new (&this->as.Identifier.name) (decltype(this->as.Identifier.name))(rhs.as.Identifier.name);
new (&this->as.Identifier.span) (decltype(this->as.Identifier.span))(rhs.as.Identifier.span);
break;
case 4 /* Semicolon */:
new (&this->as.Semicolon.value) (decltype(this->as.Semicolon.value))(rhs.as.Semicolon.value);
break;
case 5 /* Colon */:
new (&this->as.Colon.value) (decltype(this->as.Colon.value))(rhs.as.Colon.value);
break;
case 6 /* ColonColon */:
new (&this->as.ColonColon.value) (decltype(this->as.ColonColon.value))(rhs.as.ColonColon.value);
break;
case 7 /* LParen */:
new (&this->as.LParen.value) (decltype(this->as.LParen.value))(rhs.as.LParen.value);
break;
case 8 /* RParen */:
new (&this->as.RParen.value) (decltype(this->as.RParen.value))(rhs.as.RParen.value);
break;
case 9 /* LCurly */:
new (&this->as.LCurly.value) (decltype(this->as.LCurly.value))(rhs.as.LCurly.value);
break;
case 10 /* RCurly */:
new (&this->as.RCurly.value) (decltype(this->as.RCurly.value))(rhs.as.RCurly.value);
break;
case 11 /* LSquare */:
new (&this->as.LSquare.value) (decltype(this->as.LSquare.value))(rhs.as.LSquare.value);
break;
case 12 /* RSquare */:
new (&this->as.RSquare.value) (decltype(this->as.RSquare.value))(rhs.as.RSquare.value);
break;
case 13 /* PercentSign */:
new (&this->as.PercentSign.value) (decltype(this->as.PercentSign.value))(rhs.as.PercentSign.value);
break;
case 14 /* Plus */:
new (&this->as.Plus.value) (decltype(this->as.Plus.value))(rhs.as.Plus.value);
break;
case 15 /* Minus */:
new (&this->as.Minus.value) (decltype(this->as.Minus.value))(rhs.as.Minus.value);
break;
case 16 /* Equal */:
new (&this->as.Equal.value) (decltype(this->as.Equal.value))(rhs.as.Equal.value);
break;
case 17 /* PlusEqual */:
new (&this->as.PlusEqual.value) (decltype(this->as.PlusEqual.value))(rhs.as.PlusEqual.value);
break;
case 18 /* PlusPlus */:
new (&this->as.PlusPlus.value) (decltype(this->as.PlusPlus.value))(rhs.as.PlusPlus.value);
break;
case 19 /* MinusEqual */:
new (&this->as.MinusEqual.value) (decltype(this->as.MinusEqual.value))(rhs.as.MinusEqual.value);
break;
case 20 /* MinusMinus */:
new (&this->as.MinusMinus.value) (decltype(this->as.MinusMinus.value))(rhs.as.MinusMinus.value);
break;
case 21 /* AsteriskEqual */:
new (&this->as.AsteriskEqual.value) (decltype(this->as.AsteriskEqual.value))(rhs.as.AsteriskEqual.value);
break;
case 22 /* ForwardSlashEqual */:
new (&this->as.ForwardSlashEqual.value) (decltype(this->as.ForwardSlashEqual.value))(rhs.as.ForwardSlashEqual.value);
break;
case 23 /* PercentSignEqual */:
new (&this->as.PercentSignEqual.value) (decltype(this->as.PercentSignEqual.value))(rhs.as.PercentSignEqual.value);
break;
case 24 /* NotEqual */:
new (&this->as.NotEqual.value) (decltype(this->as.NotEqual.value))(rhs.as.NotEqual.value);
break;
case 25 /* DoubleEqual */:
new (&this->as.DoubleEqual.value) (decltype(this->as.DoubleEqual.value))(rhs.as.DoubleEqual.value);
break;
case 26 /* GreaterThan */:
new (&this->as.GreaterThan.value) (decltype(this->as.GreaterThan.value))(rhs.as.GreaterThan.value);
break;
case 27 /* GreaterThanOrEqual */:
new (&this->as.GreaterThanOrEqual.value) (decltype(this->as.GreaterThanOrEqual.value))(rhs.as.GreaterThanOrEqual.value);
break;
case 28 /* LessThan */:
new (&this->as.LessThan.value) (decltype(this->as.LessThan.value))(rhs.as.LessThan.value);
break;
case 29 /* LessThanOrEqual */:
new (&this->as.LessThanOrEqual.value) (decltype(this->as.LessThanOrEqual.value))(rhs.as.LessThanOrEqual.value);
break;
case 30 /* LeftArithmeticShift */:
new (&this->as.LeftArithmeticShift.value) (decltype(this->as.LeftArithmeticShift.value))(rhs.as.LeftArithmeticShift.value);
break;
case 31 /* LeftShift */:
new (&this->as.LeftShift.value) (decltype(this->as.LeftShift.value))(rhs.as.LeftShift.value);
break;
case 32 /* LeftShiftEqual */:
new (&this->as.LeftShiftEqual.value) (decltype(this->as.LeftShiftEqual.value))(rhs.as.LeftShiftEqual.value);
break;
case 33 /* RightShift */:
new (&this->as.RightShift.value) (decltype(this->as.RightShift.value))(rhs.as.RightShift.value);
break;
case 34 /* RightArithmeticShift */:
new (&this->as.RightArithmeticShift.value) (decltype(this->as.RightArithmeticShift.value))(rhs.as.RightArithmeticShift.value);
break;
case 35 /* RightShiftEqual */:
new (&this->as.RightShiftEqual.value) (decltype(this->as.RightShiftEqual.value))(rhs.as.RightShiftEqual.value);
break;
case 36 /* Asterisk */:
new (&this->as.Asterisk.value) (decltype(this->as.Asterisk.value))(rhs.as.Asterisk.value);
break;
case 37 /* Ampersand */:
new (&this->as.Ampersand.value) (decltype(this->as.Ampersand.value))(rhs.as.Ampersand.value);
break;
case 38 /* AmpersandEqual */:
new (&this->as.AmpersandEqual.value) (decltype(this->as.AmpersandEqual.value))(rhs.as.AmpersandEqual.value);
break;
case 39 /* AmpersandAmpersand */:
new (&this->as.AmpersandAmpersand.value) (decltype(this->as.AmpersandAmpersand.value))(rhs.as.AmpersandAmpersand.value);
break;
case 40 /* Pipe */:
new (&this->as.Pipe.value) (decltype(this->as.Pipe.value))(rhs.as.Pipe.value);
break;
case 41 /* PipeEqual */:
new (&this->as.PipeEqual.value) (decltype(this->as.PipeEqual.value))(rhs.as.PipeEqual.value);
break;
case 42 /* PipePipe */:
new (&this->as.PipePipe.value) (decltype(this->as.PipePipe.value))(rhs.as.PipePipe.value);
break;
case 43 /* Caret */:
new (&this->as.Caret.value) (decltype(this->as.Caret.value))(rhs.as.Caret.value);
break;
case 44 /* CaretEqual */:
new (&this->as.CaretEqual.value) (decltype(this->as.CaretEqual.value))(rhs.as.CaretEqual.value);
break;
case 45 /* Dollar */:
new (&this->as.Dollar.value) (decltype(this->as.Dollar.value))(rhs.as.Dollar.value);
break;
case 46 /* Tilde */:
new (&this->as.Tilde.value) (decltype(this->as.Tilde.value))(rhs.as.Tilde.value);
break;
case 47 /* ForwardSlash */:
new (&this->as.ForwardSlash.value) (decltype(this->as.ForwardSlash.value))(rhs.as.ForwardSlash.value);
break;
case 48 /* ExclamationPoint */:
new (&this->as.ExclamationPoint.value) (decltype(this->as.ExclamationPoint.value))(rhs.as.ExclamationPoint.value);
break;
case 49 /* QuestionMark */:
new (&this->as.QuestionMark.value) (decltype(this->as.QuestionMark.value))(rhs.as.QuestionMark.value);
break;
case 50 /* QuestionMarkQuestionMark */:
new (&this->as.QuestionMarkQuestionMark.value) (decltype(this->as.QuestionMarkQuestionMark.value))(rhs.as.QuestionMarkQuestionMark.value);
break;
case 51 /* QuestionMarkQuestionMarkEqual */:
new (&this->as.QuestionMarkQuestionMarkEqual.value) (decltype(this->as.QuestionMarkQuestionMarkEqual.value))(rhs.as.QuestionMarkQuestionMarkEqual.value);
break;
case 52 /* Comma */:
new (&this->as.Comma.value) (decltype(this->as.Comma.value))(rhs.as.Comma.value);
break;
case 53 /* Dot */:
new (&this->as.Dot.value) (decltype(this->as.Dot.value))(rhs.as.Dot.value);
break;
case 54 /* DotDot */:
new (&this->as.DotDot.value) (decltype(this->as.DotDot.value))(rhs.as.DotDot.value);
break;
case 55 /* Eol */:
new (&this->as.Eol.comment) (decltype(this->as.Eol.comment))(rhs.as.Eol.comment);
new (&this->as.Eol.span) (decltype(this->as.Eol.span))(rhs.as.Eol.span);
break;
case 56 /* Eof */:
new (&this->as.Eof.value) (decltype(this->as.Eof.value))(rhs.as.Eof.value);
break;
case 57 /* FatArrow */:
new (&this->as.FatArrow.value) (decltype(this->as.FatArrow.value))(rhs.as.FatArrow.value);
break;
case 58 /* Arrow */:
new (&this->as.Arrow.value) (decltype(this->as.Arrow.value))(rhs.as.Arrow.value);
break;
case 59 /* And */:
new (&this->as.And.value) (decltype(this->as.And.value))(rhs.as.And.value);
break;
case 60 /* Anon */:
new (&this->as.Anon.value) (decltype(this->as.Anon.value))(rhs.as.Anon.value);
break;
case 61 /* As */:
new (&this->as.As.value) (decltype(this->as.As.value))(rhs.as.As.value);
break;
case 62 /* Boxed */:
new (&this->as.Boxed.value) (decltype(this->as.Boxed.value))(rhs.as.Boxed.value);
break;
case 63 /* Break */:
new (&this->as.Break.value) (decltype(this->as.Break.value))(rhs.as.Break.value);
break;
case 64 /* Catch */:
new (&this->as.Catch.value) (decltype(this->as.Catch.value))(rhs.as.Catch.value);
break;
case 65 /* Class */:
new (&this->as.Class.value) (decltype(this->as.Class.value))(rhs.as.Class.value);
break;
case 66 /* Continue */:
new (&this->as.Continue.value) (decltype(this->as.Continue.value))(rhs.as.Continue.value);
break;
case 67 /* Cpp */:
new (&this->as.Cpp.value) (decltype(this->as.Cpp.value))(rhs.as.Cpp.value);
break;
case 68 /* Defer */:
new (&this->as.Defer.value) (decltype(this->as.Defer.value))(rhs.as.Defer.value);
break;
case 69 /* Destructor */:
new (&this->as.Destructor.value) (decltype(this->as.Destructor.value))(rhs.as.Destructor.value);
break;
case 70 /* Else */:
new (&this->as.Else.value) (decltype(this->as.Else.value))(rhs.as.Else.value);
break;
case 71 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(rhs.as.Enum.value);
break;
case 72 /* Extern */:
new (&this->as.Extern.value) (decltype(this->as.Extern.value))(rhs.as.Extern.value);
break;
case 73 /* False */:
new (&this->as.False.value) (decltype(this->as.False.value))(rhs.as.False.value);
break;
case 74 /* For */:
new (&this->as.For.value) (decltype(this->as.For.value))(rhs.as.For.value);
break;
case 75 /* Fn */:
new (&this->as.Fn.value) (decltype(this->as.Fn.value))(rhs.as.Fn.value);
break;
case 76 /* Comptime */:
new (&this->as.Comptime.value) (decltype(this->as.Comptime.value))(rhs.as.Comptime.value);
break;
case 77 /* If */:
new (&this->as.If.value) (decltype(this->as.If.value))(rhs.as.If.value);
break;
case 78 /* Import */:
new (&this->as.Import.value) (decltype(this->as.Import.value))(rhs.as.Import.value);
break;
case 79 /* In */:
new (&this->as.In.value) (decltype(this->as.In.value))(rhs.as.In.value);
break;
case 80 /* Is */:
new (&this->as.Is.value) (decltype(this->as.Is.value))(rhs.as.Is.value);
break;
case 81 /* Let */:
new (&this->as.Let.value) (decltype(this->as.Let.value))(rhs.as.Let.value);
break;
case 82 /* Loop */:
new (&this->as.Loop.value) (decltype(this->as.Loop.value))(rhs.as.Loop.value);
break;
case 83 /* Match */:
new (&this->as.Match.value) (decltype(this->as.Match.value))(rhs.as.Match.value);
break;
case 84 /* Mut */:
new (&this->as.Mut.value) (decltype(this->as.Mut.value))(rhs.as.Mut.value);
break;
case 85 /* Namespace */:
new (&this->as.Namespace.value) (decltype(this->as.Namespace.value))(rhs.as.Namespace.value);
break;
case 86 /* Not */:
new (&this->as.Not.value) (decltype(this->as.Not.value))(rhs.as.Not.value);
break;
case 87 /* Or */:
new (&this->as.Or.value) (decltype(this->as.Or.value))(rhs.as.Or.value);
break;
case 88 /* Override */:
new (&this->as.Override.value) (decltype(this->as.Override.value))(rhs.as.Override.value);
break;
case 89 /* Private */:
new (&this->as.Private.value) (decltype(this->as.Private.value))(rhs.as.Private.value);
break;
case 90 /* Public */:
new (&this->as.Public.value) (decltype(this->as.Public.value))(rhs.as.Public.value);
break;
case 91 /* Raw */:
new (&this->as.Raw.value) (decltype(this->as.Raw.value))(rhs.as.Raw.value);
break;
case 92 /* Reflect */:
new (&this->as.Reflect.value) (decltype(this->as.Reflect.value))(rhs.as.Reflect.value);
break;
case 93 /* Return */:
new (&this->as.Return.value) (decltype(this->as.Return.value))(rhs.as.Return.value);
break;
case 94 /* Restricted */:
new (&this->as.Restricted.value) (decltype(this->as.Restricted.value))(rhs.as.Restricted.value);
break;
case 95 /* Sizeof */:
new (&this->as.Sizeof.value) (decltype(this->as.Sizeof.value))(rhs.as.Sizeof.value);
break;
case 96 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(rhs.as.Struct.value);
break;
case 97 /* This */:
new (&this->as.This.value) (decltype(this->as.This.value))(rhs.as.This.value);
break;
case 98 /* Throw */:
new (&this->as.Throw.value) (decltype(this->as.Throw.value))(rhs.as.Throw.value);
break;
case 99 /* Throws */:
new (&this->as.Throws.value) (decltype(this->as.Throws.value))(rhs.as.Throws.value);
break;
case 100 /* True */:
new (&this->as.True.value) (decltype(this->as.True.value))(rhs.as.True.value);
break;
case 101 /* Try */:
new (&this->as.Try.value) (decltype(this->as.Try.value))(rhs.as.Try.value);
break;
case 102 /* Unsafe */:
new (&this->as.Unsafe.value) (decltype(this->as.Unsafe.value))(rhs.as.Unsafe.value);
break;
case 103 /* Virtual */:
new (&this->as.Virtual.value) (decltype(this->as.Virtual.value))(rhs.as.Virtual.value);
break;
case 104 /* Weak */:
new (&this->as.Weak.value) (decltype(this->as.Weak.value))(rhs.as.Weak.value);
break;
case 105 /* While */:
new (&this->as.While.value) (decltype(this->as.While.value))(rhs.as.While.value);
break;
case 106 /* Yield */:
new (&this->as.Yield.value) (decltype(this->as.Yield.value))(rhs.as.Yield.value);
break;
case 107 /* Guard */:
new (&this->as.Guard.value) (decltype(this->as.Guard.value))(rhs.as.Guard.value);
break;
case 108 /* Implements */:
new (&this->as.Implements.value) (decltype(this->as.Implements.value))(rhs.as.Implements.value);
break;
case 109 /* Requires */:
new (&this->as.Requires.value) (decltype(this->as.Requires.value))(rhs.as.Requires.value);
break;
case 110 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(rhs.as.Trait.value);
break;
case 111 /* Garbage */:
new (&this->as.Garbage.consumed) (decltype(this->as.Garbage.consumed))(rhs.as.Garbage.consumed);
new (&this->as.Garbage.span) (decltype(this->as.Garbage.span))(rhs.as.Garbage.span);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
Token& Token::operator=(Token &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* SingleQuotedString */:
new (&this->as.SingleQuotedString.quote) (decltype(this->as.SingleQuotedString.quote))(move(rhs.as.SingleQuotedString.quote));
new (&this->as.SingleQuotedString.prefix) (decltype(this->as.SingleQuotedString.prefix))(move(rhs.as.SingleQuotedString.prefix));
new (&this->as.SingleQuotedString.span) (decltype(this->as.SingleQuotedString.span))(move(rhs.as.SingleQuotedString.span));
break;
case 1 /* QuotedString */:
new (&this->as.QuotedString.quote) (decltype(this->as.QuotedString.quote))(move(rhs.as.QuotedString.quote));
new (&this->as.QuotedString.span) (decltype(this->as.QuotedString.span))(move(rhs.as.QuotedString.span));
break;
case 2 /* Number */:
new (&this->as.Number.prefix) (decltype(this->as.Number.prefix))(move(rhs.as.Number.prefix));
new (&this->as.Number.number) (decltype(this->as.Number.number))(move(rhs.as.Number.number));
new (&this->as.Number.suffix) (decltype(this->as.Number.suffix))(move(rhs.as.Number.suffix));
new (&this->as.Number.span) (decltype(this->as.Number.span))(move(rhs.as.Number.span));
break;
case 3 /* Identifier */:
new (&this->as.Identifier.name) (decltype(this->as.Identifier.name))(move(rhs.as.Identifier.name));
new (&this->as.Identifier.span) (decltype(this->as.Identifier.span))(move(rhs.as.Identifier.span));
break;
case 4 /* Semicolon */:
new (&this->as.Semicolon.value) (decltype(this->as.Semicolon.value))(move(rhs.as.Semicolon.value));
break;
case 5 /* Colon */:
new (&this->as.Colon.value) (decltype(this->as.Colon.value))(move(rhs.as.Colon.value));
break;
case 6 /* ColonColon */:
new (&this->as.ColonColon.value) (decltype(this->as.ColonColon.value))(move(rhs.as.ColonColon.value));
break;
case 7 /* LParen */:
new (&this->as.LParen.value) (decltype(this->as.LParen.value))(move(rhs.as.LParen.value));
break;
case 8 /* RParen */:
new (&this->as.RParen.value) (decltype(this->as.RParen.value))(move(rhs.as.RParen.value));
break;
case 9 /* LCurly */:
new (&this->as.LCurly.value) (decltype(this->as.LCurly.value))(move(rhs.as.LCurly.value));
break;
case 10 /* RCurly */:
new (&this->as.RCurly.value) (decltype(this->as.RCurly.value))(move(rhs.as.RCurly.value));
break;
case 11 /* LSquare */:
new (&this->as.LSquare.value) (decltype(this->as.LSquare.value))(move(rhs.as.LSquare.value));
break;
case 12 /* RSquare */:
new (&this->as.RSquare.value) (decltype(this->as.RSquare.value))(move(rhs.as.RSquare.value));
break;
case 13 /* PercentSign */:
new (&this->as.PercentSign.value) (decltype(this->as.PercentSign.value))(move(rhs.as.PercentSign.value));
break;
case 14 /* Plus */:
new (&this->as.Plus.value) (decltype(this->as.Plus.value))(move(rhs.as.Plus.value));
break;
case 15 /* Minus */:
new (&this->as.Minus.value) (decltype(this->as.Minus.value))(move(rhs.as.Minus.value));
break;
case 16 /* Equal */:
new (&this->as.Equal.value) (decltype(this->as.Equal.value))(move(rhs.as.Equal.value));
break;
case 17 /* PlusEqual */:
new (&this->as.PlusEqual.value) (decltype(this->as.PlusEqual.value))(move(rhs.as.PlusEqual.value));
break;
case 18 /* PlusPlus */:
new (&this->as.PlusPlus.value) (decltype(this->as.PlusPlus.value))(move(rhs.as.PlusPlus.value));
break;
case 19 /* MinusEqual */:
new (&this->as.MinusEqual.value) (decltype(this->as.MinusEqual.value))(move(rhs.as.MinusEqual.value));
break;
case 20 /* MinusMinus */:
new (&this->as.MinusMinus.value) (decltype(this->as.MinusMinus.value))(move(rhs.as.MinusMinus.value));
break;
case 21 /* AsteriskEqual */:
new (&this->as.AsteriskEqual.value) (decltype(this->as.AsteriskEqual.value))(move(rhs.as.AsteriskEqual.value));
break;
case 22 /* ForwardSlashEqual */:
new (&this->as.ForwardSlashEqual.value) (decltype(this->as.ForwardSlashEqual.value))(move(rhs.as.ForwardSlashEqual.value));
break;
case 23 /* PercentSignEqual */:
new (&this->as.PercentSignEqual.value) (decltype(this->as.PercentSignEqual.value))(move(rhs.as.PercentSignEqual.value));
break;
case 24 /* NotEqual */:
new (&this->as.NotEqual.value) (decltype(this->as.NotEqual.value))(move(rhs.as.NotEqual.value));
break;
case 25 /* DoubleEqual */:
new (&this->as.DoubleEqual.value) (decltype(this->as.DoubleEqual.value))(move(rhs.as.DoubleEqual.value));
break;
case 26 /* GreaterThan */:
new (&this->as.GreaterThan.value) (decltype(this->as.GreaterThan.value))(move(rhs.as.GreaterThan.value));
break;
case 27 /* GreaterThanOrEqual */:
new (&this->as.GreaterThanOrEqual.value) (decltype(this->as.GreaterThanOrEqual.value))(move(rhs.as.GreaterThanOrEqual.value));
break;
case 28 /* LessThan */:
new (&this->as.LessThan.value) (decltype(this->as.LessThan.value))(move(rhs.as.LessThan.value));
break;
case 29 /* LessThanOrEqual */:
new (&this->as.LessThanOrEqual.value) (decltype(this->as.LessThanOrEqual.value))(move(rhs.as.LessThanOrEqual.value));
break;
case 30 /* LeftArithmeticShift */:
new (&this->as.LeftArithmeticShift.value) (decltype(this->as.LeftArithmeticShift.value))(move(rhs.as.LeftArithmeticShift.value));
break;
case 31 /* LeftShift */:
new (&this->as.LeftShift.value) (decltype(this->as.LeftShift.value))(move(rhs.as.LeftShift.value));
break;
case 32 /* LeftShiftEqual */:
new (&this->as.LeftShiftEqual.value) (decltype(this->as.LeftShiftEqual.value))(move(rhs.as.LeftShiftEqual.value));
break;
case 33 /* RightShift */:
new (&this->as.RightShift.value) (decltype(this->as.RightShift.value))(move(rhs.as.RightShift.value));
break;
case 34 /* RightArithmeticShift */:
new (&this->as.RightArithmeticShift.value) (decltype(this->as.RightArithmeticShift.value))(move(rhs.as.RightArithmeticShift.value));
break;
case 35 /* RightShiftEqual */:
new (&this->as.RightShiftEqual.value) (decltype(this->as.RightShiftEqual.value))(move(rhs.as.RightShiftEqual.value));
break;
case 36 /* Asterisk */:
new (&this->as.Asterisk.value) (decltype(this->as.Asterisk.value))(move(rhs.as.Asterisk.value));
break;
case 37 /* Ampersand */:
new (&this->as.Ampersand.value) (decltype(this->as.Ampersand.value))(move(rhs.as.Ampersand.value));
break;
case 38 /* AmpersandEqual */:
new (&this->as.AmpersandEqual.value) (decltype(this->as.AmpersandEqual.value))(move(rhs.as.AmpersandEqual.value));
break;
case 39 /* AmpersandAmpersand */:
new (&this->as.AmpersandAmpersand.value) (decltype(this->as.AmpersandAmpersand.value))(move(rhs.as.AmpersandAmpersand.value));
break;
case 40 /* Pipe */:
new (&this->as.Pipe.value) (decltype(this->as.Pipe.value))(move(rhs.as.Pipe.value));
break;
case 41 /* PipeEqual */:
new (&this->as.PipeEqual.value) (decltype(this->as.PipeEqual.value))(move(rhs.as.PipeEqual.value));
break;
case 42 /* PipePipe */:
new (&this->as.PipePipe.value) (decltype(this->as.PipePipe.value))(move(rhs.as.PipePipe.value));
break;
case 43 /* Caret */:
new (&this->as.Caret.value) (decltype(this->as.Caret.value))(move(rhs.as.Caret.value));
break;
case 44 /* CaretEqual */:
new (&this->as.CaretEqual.value) (decltype(this->as.CaretEqual.value))(move(rhs.as.CaretEqual.value));
break;
case 45 /* Dollar */:
new (&this->as.Dollar.value) (decltype(this->as.Dollar.value))(move(rhs.as.Dollar.value));
break;
case 46 /* Tilde */:
new (&this->as.Tilde.value) (decltype(this->as.Tilde.value))(move(rhs.as.Tilde.value));
break;
case 47 /* ForwardSlash */:
new (&this->as.ForwardSlash.value) (decltype(this->as.ForwardSlash.value))(move(rhs.as.ForwardSlash.value));
break;
case 48 /* ExclamationPoint */:
new (&this->as.ExclamationPoint.value) (decltype(this->as.ExclamationPoint.value))(move(rhs.as.ExclamationPoint.value));
break;
case 49 /* QuestionMark */:
new (&this->as.QuestionMark.value) (decltype(this->as.QuestionMark.value))(move(rhs.as.QuestionMark.value));
break;
case 50 /* QuestionMarkQuestionMark */:
new (&this->as.QuestionMarkQuestionMark.value) (decltype(this->as.QuestionMarkQuestionMark.value))(move(rhs.as.QuestionMarkQuestionMark.value));
break;
case 51 /* QuestionMarkQuestionMarkEqual */:
new (&this->as.QuestionMarkQuestionMarkEqual.value) (decltype(this->as.QuestionMarkQuestionMarkEqual.value))(move(rhs.as.QuestionMarkQuestionMarkEqual.value));
break;
case 52 /* Comma */:
new (&this->as.Comma.value) (decltype(this->as.Comma.value))(move(rhs.as.Comma.value));
break;
case 53 /* Dot */:
new (&this->as.Dot.value) (decltype(this->as.Dot.value))(move(rhs.as.Dot.value));
break;
case 54 /* DotDot */:
new (&this->as.DotDot.value) (decltype(this->as.DotDot.value))(move(rhs.as.DotDot.value));
break;
case 55 /* Eol */:
new (&this->as.Eol.comment) (decltype(this->as.Eol.comment))(move(rhs.as.Eol.comment));
new (&this->as.Eol.span) (decltype(this->as.Eol.span))(move(rhs.as.Eol.span));
break;
case 56 /* Eof */:
new (&this->as.Eof.value) (decltype(this->as.Eof.value))(move(rhs.as.Eof.value));
break;
case 57 /* FatArrow */:
new (&this->as.FatArrow.value) (decltype(this->as.FatArrow.value))(move(rhs.as.FatArrow.value));
break;
case 58 /* Arrow */:
new (&this->as.Arrow.value) (decltype(this->as.Arrow.value))(move(rhs.as.Arrow.value));
break;
case 59 /* And */:
new (&this->as.And.value) (decltype(this->as.And.value))(move(rhs.as.And.value));
break;
case 60 /* Anon */:
new (&this->as.Anon.value) (decltype(this->as.Anon.value))(move(rhs.as.Anon.value));
break;
case 61 /* As */:
new (&this->as.As.value) (decltype(this->as.As.value))(move(rhs.as.As.value));
break;
case 62 /* Boxed */:
new (&this->as.Boxed.value) (decltype(this->as.Boxed.value))(move(rhs.as.Boxed.value));
break;
case 63 /* Break */:
new (&this->as.Break.value) (decltype(this->as.Break.value))(move(rhs.as.Break.value));
break;
case 64 /* Catch */:
new (&this->as.Catch.value) (decltype(this->as.Catch.value))(move(rhs.as.Catch.value));
break;
case 65 /* Class */:
new (&this->as.Class.value) (decltype(this->as.Class.value))(move(rhs.as.Class.value));
break;
case 66 /* Continue */:
new (&this->as.Continue.value) (decltype(this->as.Continue.value))(move(rhs.as.Continue.value));
break;
case 67 /* Cpp */:
new (&this->as.Cpp.value) (decltype(this->as.Cpp.value))(move(rhs.as.Cpp.value));
break;
case 68 /* Defer */:
new (&this->as.Defer.value) (decltype(this->as.Defer.value))(move(rhs.as.Defer.value));
break;
case 69 /* Destructor */:
new (&this->as.Destructor.value) (decltype(this->as.Destructor.value))(move(rhs.as.Destructor.value));
break;
case 70 /* Else */:
new (&this->as.Else.value) (decltype(this->as.Else.value))(move(rhs.as.Else.value));
break;
case 71 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(move(rhs.as.Enum.value));
break;
case 72 /* Extern */:
new (&this->as.Extern.value) (decltype(this->as.Extern.value))(move(rhs.as.Extern.value));
break;
case 73 /* False */:
new (&this->as.False.value) (decltype(this->as.False.value))(move(rhs.as.False.value));
break;
case 74 /* For */:
new (&this->as.For.value) (decltype(this->as.For.value))(move(rhs.as.For.value));
break;
case 75 /* Fn */:
new (&this->as.Fn.value) (decltype(this->as.Fn.value))(move(rhs.as.Fn.value));
break;
case 76 /* Comptime */:
new (&this->as.Comptime.value) (decltype(this->as.Comptime.value))(move(rhs.as.Comptime.value));
break;
case 77 /* If */:
new (&this->as.If.value) (decltype(this->as.If.value))(move(rhs.as.If.value));
break;
case 78 /* Import */:
new (&this->as.Import.value) (decltype(this->as.Import.value))(move(rhs.as.Import.value));
break;
case 79 /* In */:
new (&this->as.In.value) (decltype(this->as.In.value))(move(rhs.as.In.value));
break;
case 80 /* Is */:
new (&this->as.Is.value) (decltype(this->as.Is.value))(move(rhs.as.Is.value));
break;
case 81 /* Let */:
new (&this->as.Let.value) (decltype(this->as.Let.value))(move(rhs.as.Let.value));
break;
case 82 /* Loop */:
new (&this->as.Loop.value) (decltype(this->as.Loop.value))(move(rhs.as.Loop.value));
break;
case 83 /* Match */:
new (&this->as.Match.value) (decltype(this->as.Match.value))(move(rhs.as.Match.value));
break;
case 84 /* Mut */:
new (&this->as.Mut.value) (decltype(this->as.Mut.value))(move(rhs.as.Mut.value));
break;
case 85 /* Namespace */:
new (&this->as.Namespace.value) (decltype(this->as.Namespace.value))(move(rhs.as.Namespace.value));
break;
case 86 /* Not */:
new (&this->as.Not.value) (decltype(this->as.Not.value))(move(rhs.as.Not.value));
break;
case 87 /* Or */:
new (&this->as.Or.value) (decltype(this->as.Or.value))(move(rhs.as.Or.value));
break;
case 88 /* Override */:
new (&this->as.Override.value) (decltype(this->as.Override.value))(move(rhs.as.Override.value));
break;
case 89 /* Private */:
new (&this->as.Private.value) (decltype(this->as.Private.value))(move(rhs.as.Private.value));
break;
case 90 /* Public */:
new (&this->as.Public.value) (decltype(this->as.Public.value))(move(rhs.as.Public.value));
break;
case 91 /* Raw */:
new (&this->as.Raw.value) (decltype(this->as.Raw.value))(move(rhs.as.Raw.value));
break;
case 92 /* Reflect */:
new (&this->as.Reflect.value) (decltype(this->as.Reflect.value))(move(rhs.as.Reflect.value));
break;
case 93 /* Return */:
new (&this->as.Return.value) (decltype(this->as.Return.value))(move(rhs.as.Return.value));
break;
case 94 /* Restricted */:
new (&this->as.Restricted.value) (decltype(this->as.Restricted.value))(move(rhs.as.Restricted.value));
break;
case 95 /* Sizeof */:
new (&this->as.Sizeof.value) (decltype(this->as.Sizeof.value))(move(rhs.as.Sizeof.value));
break;
case 96 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(move(rhs.as.Struct.value));
break;
case 97 /* This */:
new (&this->as.This.value) (decltype(this->as.This.value))(move(rhs.as.This.value));
break;
case 98 /* Throw */:
new (&this->as.Throw.value) (decltype(this->as.Throw.value))(move(rhs.as.Throw.value));
break;
case 99 /* Throws */:
new (&this->as.Throws.value) (decltype(this->as.Throws.value))(move(rhs.as.Throws.value));
break;
case 100 /* True */:
new (&this->as.True.value) (decltype(this->as.True.value))(move(rhs.as.True.value));
break;
case 101 /* Try */:
new (&this->as.Try.value) (decltype(this->as.Try.value))(move(rhs.as.Try.value));
break;
case 102 /* Unsafe */:
new (&this->as.Unsafe.value) (decltype(this->as.Unsafe.value))(move(rhs.as.Unsafe.value));
break;
case 103 /* Virtual */:
new (&this->as.Virtual.value) (decltype(this->as.Virtual.value))(move(rhs.as.Virtual.value));
break;
case 104 /* Weak */:
new (&this->as.Weak.value) (decltype(this->as.Weak.value))(move(rhs.as.Weak.value));
break;
case 105 /* While */:
new (&this->as.While.value) (decltype(this->as.While.value))(move(rhs.as.While.value));
break;
case 106 /* Yield */:
new (&this->as.Yield.value) (decltype(this->as.Yield.value))(move(rhs.as.Yield.value));
break;
case 107 /* Guard */:
new (&this->as.Guard.value) (decltype(this->as.Guard.value))(move(rhs.as.Guard.value));
break;
case 108 /* Implements */:
new (&this->as.Implements.value) (decltype(this->as.Implements.value))(move(rhs.as.Implements.value));
break;
case 109 /* Requires */:
new (&this->as.Requires.value) (decltype(this->as.Requires.value))(move(rhs.as.Requires.value));
break;
case 110 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(move(rhs.as.Trait.value));
break;
case 111 /* Garbage */:
new (&this->as.Garbage.consumed) (decltype(this->as.Garbage.consumed))(move(rhs.as.Garbage.consumed));
new (&this->as.Garbage.span) (decltype(this->as.Garbage.span))(move(rhs.as.Garbage.span));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* SingleQuotedString */:
this->as.SingleQuotedString.quote = move(rhs.as.SingleQuotedString.quote);
this->as.SingleQuotedString.prefix = move(rhs.as.SingleQuotedString.prefix);
this->as.SingleQuotedString.span = move(rhs.as.SingleQuotedString.span);
break;
case 1 /* QuotedString */:
this->as.QuotedString.quote = move(rhs.as.QuotedString.quote);
this->as.QuotedString.span = move(rhs.as.QuotedString.span);
break;
case 2 /* Number */:
this->as.Number.prefix = move(rhs.as.Number.prefix);
this->as.Number.number = move(rhs.as.Number.number);
this->as.Number.suffix = move(rhs.as.Number.suffix);
this->as.Number.span = move(rhs.as.Number.span);
break;
case 3 /* Identifier */:
this->as.Identifier.name = move(rhs.as.Identifier.name);
this->as.Identifier.span = move(rhs.as.Identifier.span);
break;
case 4 /* Semicolon */:
this->as.Semicolon.value = move(rhs.as.Semicolon.value);
break;
case 5 /* Colon */:
this->as.Colon.value = move(rhs.as.Colon.value);
break;
case 6 /* ColonColon */:
this->as.ColonColon.value = move(rhs.as.ColonColon.value);
break;
case 7 /* LParen */:
this->as.LParen.value = move(rhs.as.LParen.value);
break;
case 8 /* RParen */:
this->as.RParen.value = move(rhs.as.RParen.value);
break;
case 9 /* LCurly */:
this->as.LCurly.value = move(rhs.as.LCurly.value);
break;
case 10 /* RCurly */:
this->as.RCurly.value = move(rhs.as.RCurly.value);
break;
case 11 /* LSquare */:
this->as.LSquare.value = move(rhs.as.LSquare.value);
break;
case 12 /* RSquare */:
this->as.RSquare.value = move(rhs.as.RSquare.value);
break;
case 13 /* PercentSign */:
this->as.PercentSign.value = move(rhs.as.PercentSign.value);
break;
case 14 /* Plus */:
this->as.Plus.value = move(rhs.as.Plus.value);
break;
case 15 /* Minus */:
this->as.Minus.value = move(rhs.as.Minus.value);
break;
case 16 /* Equal */:
this->as.Equal.value = move(rhs.as.Equal.value);
break;
case 17 /* PlusEqual */:
this->as.PlusEqual.value = move(rhs.as.PlusEqual.value);
break;
case 18 /* PlusPlus */:
this->as.PlusPlus.value = move(rhs.as.PlusPlus.value);
break;
case 19 /* MinusEqual */:
this->as.MinusEqual.value = move(rhs.as.MinusEqual.value);
break;
case 20 /* MinusMinus */:
this->as.MinusMinus.value = move(rhs.as.MinusMinus.value);
break;
case 21 /* AsteriskEqual */:
this->as.AsteriskEqual.value = move(rhs.as.AsteriskEqual.value);
break;
case 22 /* ForwardSlashEqual */:
this->as.ForwardSlashEqual.value = move(rhs.as.ForwardSlashEqual.value);
break;
case 23 /* PercentSignEqual */:
this->as.PercentSignEqual.value = move(rhs.as.PercentSignEqual.value);
break;
case 24 /* NotEqual */:
this->as.NotEqual.value = move(rhs.as.NotEqual.value);
break;
case 25 /* DoubleEqual */:
this->as.DoubleEqual.value = move(rhs.as.DoubleEqual.value);
break;
case 26 /* GreaterThan */:
this->as.GreaterThan.value = move(rhs.as.GreaterThan.value);
break;
case 27 /* GreaterThanOrEqual */:
this->as.GreaterThanOrEqual.value = move(rhs.as.GreaterThanOrEqual.value);
break;
case 28 /* LessThan */:
this->as.LessThan.value = move(rhs.as.LessThan.value);
break;
case 29 /* LessThanOrEqual */:
this->as.LessThanOrEqual.value = move(rhs.as.LessThanOrEqual.value);
break;
case 30 /* LeftArithmeticShift */:
this->as.LeftArithmeticShift.value = move(rhs.as.LeftArithmeticShift.value);
break;
case 31 /* LeftShift */:
this->as.LeftShift.value = move(rhs.as.LeftShift.value);
break;
case 32 /* LeftShiftEqual */:
this->as.LeftShiftEqual.value = move(rhs.as.LeftShiftEqual.value);
break;
case 33 /* RightShift */:
this->as.RightShift.value = move(rhs.as.RightShift.value);
break;
case 34 /* RightArithmeticShift */:
this->as.RightArithmeticShift.value = move(rhs.as.RightArithmeticShift.value);
break;
case 35 /* RightShiftEqual */:
this->as.RightShiftEqual.value = move(rhs.as.RightShiftEqual.value);
break;
case 36 /* Asterisk */:
this->as.Asterisk.value = move(rhs.as.Asterisk.value);
break;
case 37 /* Ampersand */:
this->as.Ampersand.value = move(rhs.as.Ampersand.value);
break;
case 38 /* AmpersandEqual */:
this->as.AmpersandEqual.value = move(rhs.as.AmpersandEqual.value);
break;
case 39 /* AmpersandAmpersand */:
this->as.AmpersandAmpersand.value = move(rhs.as.AmpersandAmpersand.value);
break;
case 40 /* Pipe */:
this->as.Pipe.value = move(rhs.as.Pipe.value);
break;
case 41 /* PipeEqual */:
this->as.PipeEqual.value = move(rhs.as.PipeEqual.value);
break;
case 42 /* PipePipe */:
this->as.PipePipe.value = move(rhs.as.PipePipe.value);
break;
case 43 /* Caret */:
this->as.Caret.value = move(rhs.as.Caret.value);
break;
case 44 /* CaretEqual */:
this->as.CaretEqual.value = move(rhs.as.CaretEqual.value);
break;
case 45 /* Dollar */:
this->as.Dollar.value = move(rhs.as.Dollar.value);
break;
case 46 /* Tilde */:
this->as.Tilde.value = move(rhs.as.Tilde.value);
break;
case 47 /* ForwardSlash */:
this->as.ForwardSlash.value = move(rhs.as.ForwardSlash.value);
break;
case 48 /* ExclamationPoint */:
this->as.ExclamationPoint.value = move(rhs.as.ExclamationPoint.value);
break;
case 49 /* QuestionMark */:
this->as.QuestionMark.value = move(rhs.as.QuestionMark.value);
break;
case 50 /* QuestionMarkQuestionMark */:
this->as.QuestionMarkQuestionMark.value = move(rhs.as.QuestionMarkQuestionMark.value);
break;
case 51 /* QuestionMarkQuestionMarkEqual */:
this->as.QuestionMarkQuestionMarkEqual.value = move(rhs.as.QuestionMarkQuestionMarkEqual.value);
break;
case 52 /* Comma */:
this->as.Comma.value = move(rhs.as.Comma.value);
break;
case 53 /* Dot */:
this->as.Dot.value = move(rhs.as.Dot.value);
break;
case 54 /* DotDot */:
this->as.DotDot.value = move(rhs.as.DotDot.value);
break;
case 55 /* Eol */:
this->as.Eol.comment = move(rhs.as.Eol.comment);
this->as.Eol.span = move(rhs.as.Eol.span);
break;
case 56 /* Eof */:
this->as.Eof.value = move(rhs.as.Eof.value);
break;
case 57 /* FatArrow */:
this->as.FatArrow.value = move(rhs.as.FatArrow.value);
break;
case 58 /* Arrow */:
this->as.Arrow.value = move(rhs.as.Arrow.value);
break;
case 59 /* And */:
this->as.And.value = move(rhs.as.And.value);
break;
case 60 /* Anon */:
this->as.Anon.value = move(rhs.as.Anon.value);
break;
case 61 /* As */:
this->as.As.value = move(rhs.as.As.value);
break;
case 62 /* Boxed */:
this->as.Boxed.value = move(rhs.as.Boxed.value);
break;
case 63 /* Break */:
this->as.Break.value = move(rhs.as.Break.value);
break;
case 64 /* Catch */:
this->as.Catch.value = move(rhs.as.Catch.value);
break;
case 65 /* Class */:
this->as.Class.value = move(rhs.as.Class.value);
break;
case 66 /* Continue */:
this->as.Continue.value = move(rhs.as.Continue.value);
break;
case 67 /* Cpp */:
this->as.Cpp.value = move(rhs.as.Cpp.value);
break;
case 68 /* Defer */:
this->as.Defer.value = move(rhs.as.Defer.value);
break;
case 69 /* Destructor */:
this->as.Destructor.value = move(rhs.as.Destructor.value);
break;
case 70 /* Else */:
this->as.Else.value = move(rhs.as.Else.value);
break;
case 71 /* Enum */:
this->as.Enum.value = move(rhs.as.Enum.value);
break;
case 72 /* Extern */:
this->as.Extern.value = move(rhs.as.Extern.value);
break;
case 73 /* False */:
this->as.False.value = move(rhs.as.False.value);
break;
case 74 /* For */:
this->as.For.value = move(rhs.as.For.value);
break;
case 75 /* Fn */:
this->as.Fn.value = move(rhs.as.Fn.value);
break;
case 76 /* Comptime */:
this->as.Comptime.value = move(rhs.as.Comptime.value);
break;
case 77 /* If */:
this->as.If.value = move(rhs.as.If.value);
break;
case 78 /* Import */:
this->as.Import.value = move(rhs.as.Import.value);
break;
case 79 /* In */:
this->as.In.value = move(rhs.as.In.value);
break;
case 80 /* Is */:
this->as.Is.value = move(rhs.as.Is.value);
break;
case 81 /* Let */:
this->as.Let.value = move(rhs.as.Let.value);
break;
case 82 /* Loop */:
this->as.Loop.value = move(rhs.as.Loop.value);
break;
case 83 /* Match */:
this->as.Match.value = move(rhs.as.Match.value);
break;
case 84 /* Mut */:
this->as.Mut.value = move(rhs.as.Mut.value);
break;
case 85 /* Namespace */:
this->as.Namespace.value = move(rhs.as.Namespace.value);
break;
case 86 /* Not */:
this->as.Not.value = move(rhs.as.Not.value);
break;
case 87 /* Or */:
this->as.Or.value = move(rhs.as.Or.value);
break;
case 88 /* Override */:
this->as.Override.value = move(rhs.as.Override.value);
break;
case 89 /* Private */:
this->as.Private.value = move(rhs.as.Private.value);
break;
case 90 /* Public */:
this->as.Public.value = move(rhs.as.Public.value);
break;
case 91 /* Raw */:
this->as.Raw.value = move(rhs.as.Raw.value);
break;
case 92 /* Reflect */:
this->as.Reflect.value = move(rhs.as.Reflect.value);
break;
case 93 /* Return */:
this->as.Return.value = move(rhs.as.Return.value);
break;
case 94 /* Restricted */:
this->as.Restricted.value = move(rhs.as.Restricted.value);
break;
case 95 /* Sizeof */:
this->as.Sizeof.value = move(rhs.as.Sizeof.value);
break;
case 96 /* Struct */:
this->as.Struct.value = move(rhs.as.Struct.value);
break;
case 97 /* This */:
this->as.This.value = move(rhs.as.This.value);
break;
case 98 /* Throw */:
this->as.Throw.value = move(rhs.as.Throw.value);
break;
case 99 /* Throws */:
this->as.Throws.value = move(rhs.as.Throws.value);
break;
case 100 /* True */:
this->as.True.value = move(rhs.as.True.value);
break;
case 101 /* Try */:
this->as.Try.value = move(rhs.as.Try.value);
break;
case 102 /* Unsafe */:
this->as.Unsafe.value = move(rhs.as.Unsafe.value);
break;
case 103 /* Virtual */:
this->as.Virtual.value = move(rhs.as.Virtual.value);
break;
case 104 /* Weak */:
this->as.Weak.value = move(rhs.as.Weak.value);
break;
case 105 /* While */:
this->as.While.value = move(rhs.as.While.value);
break;
case 106 /* Yield */:
this->as.Yield.value = move(rhs.as.Yield.value);
break;
case 107 /* Guard */:
this->as.Guard.value = move(rhs.as.Guard.value);
break;
case 108 /* Implements */:
this->as.Implements.value = move(rhs.as.Implements.value);
break;
case 109 /* Requires */:
this->as.Requires.value = move(rhs.as.Requires.value);
break;
case 110 /* Trait */:
this->as.Trait.value = move(rhs.as.Trait.value);
break;
case 111 /* Garbage */:
this->as.Garbage.consumed = move(rhs.as.Garbage.consumed);
this->as.Garbage.span = move(rhs.as.Garbage.span);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
Token::Token(Token &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* SingleQuotedString */:
new (&this->as.SingleQuotedString.quote) (decltype(this->as.SingleQuotedString.quote))(move(rhs.as.SingleQuotedString.quote));
new (&this->as.SingleQuotedString.prefix) (decltype(this->as.SingleQuotedString.prefix))(move(rhs.as.SingleQuotedString.prefix));
new (&this->as.SingleQuotedString.span) (decltype(this->as.SingleQuotedString.span))(move(rhs.as.SingleQuotedString.span));
break;
case 1 /* QuotedString */:
new (&this->as.QuotedString.quote) (decltype(this->as.QuotedString.quote))(move(rhs.as.QuotedString.quote));
new (&this->as.QuotedString.span) (decltype(this->as.QuotedString.span))(move(rhs.as.QuotedString.span));
break;
case 2 /* Number */:
new (&this->as.Number.prefix) (decltype(this->as.Number.prefix))(move(rhs.as.Number.prefix));
new (&this->as.Number.number) (decltype(this->as.Number.number))(move(rhs.as.Number.number));
new (&this->as.Number.suffix) (decltype(this->as.Number.suffix))(move(rhs.as.Number.suffix));
new (&this->as.Number.span) (decltype(this->as.Number.span))(move(rhs.as.Number.span));
break;
case 3 /* Identifier */:
new (&this->as.Identifier.name) (decltype(this->as.Identifier.name))(move(rhs.as.Identifier.name));
new (&this->as.Identifier.span) (decltype(this->as.Identifier.span))(move(rhs.as.Identifier.span));
break;
case 4 /* Semicolon */:
new (&this->as.Semicolon.value) (decltype(this->as.Semicolon.value))(move(rhs.as.Semicolon.value));
break;
case 5 /* Colon */:
new (&this->as.Colon.value) (decltype(this->as.Colon.value))(move(rhs.as.Colon.value));
break;
case 6 /* ColonColon */:
new (&this->as.ColonColon.value) (decltype(this->as.ColonColon.value))(move(rhs.as.ColonColon.value));
break;
case 7 /* LParen */:
new (&this->as.LParen.value) (decltype(this->as.LParen.value))(move(rhs.as.LParen.value));
break;
case 8 /* RParen */:
new (&this->as.RParen.value) (decltype(this->as.RParen.value))(move(rhs.as.RParen.value));
break;
case 9 /* LCurly */:
new (&this->as.LCurly.value) (decltype(this->as.LCurly.value))(move(rhs.as.LCurly.value));
break;
case 10 /* RCurly */:
new (&this->as.RCurly.value) (decltype(this->as.RCurly.value))(move(rhs.as.RCurly.value));
break;
case 11 /* LSquare */:
new (&this->as.LSquare.value) (decltype(this->as.LSquare.value))(move(rhs.as.LSquare.value));
break;
case 12 /* RSquare */:
new (&this->as.RSquare.value) (decltype(this->as.RSquare.value))(move(rhs.as.RSquare.value));
break;
case 13 /* PercentSign */:
new (&this->as.PercentSign.value) (decltype(this->as.PercentSign.value))(move(rhs.as.PercentSign.value));
break;
case 14 /* Plus */:
new (&this->as.Plus.value) (decltype(this->as.Plus.value))(move(rhs.as.Plus.value));
break;
case 15 /* Minus */:
new (&this->as.Minus.value) (decltype(this->as.Minus.value))(move(rhs.as.Minus.value));
break;
case 16 /* Equal */:
new (&this->as.Equal.value) (decltype(this->as.Equal.value))(move(rhs.as.Equal.value));
break;
case 17 /* PlusEqual */:
new (&this->as.PlusEqual.value) (decltype(this->as.PlusEqual.value))(move(rhs.as.PlusEqual.value));
break;
case 18 /* PlusPlus */:
new (&this->as.PlusPlus.value) (decltype(this->as.PlusPlus.value))(move(rhs.as.PlusPlus.value));
break;
case 19 /* MinusEqual */:
new (&this->as.MinusEqual.value) (decltype(this->as.MinusEqual.value))(move(rhs.as.MinusEqual.value));
break;
case 20 /* MinusMinus */:
new (&this->as.MinusMinus.value) (decltype(this->as.MinusMinus.value))(move(rhs.as.MinusMinus.value));
break;
case 21 /* AsteriskEqual */:
new (&this->as.AsteriskEqual.value) (decltype(this->as.AsteriskEqual.value))(move(rhs.as.AsteriskEqual.value));
break;
case 22 /* ForwardSlashEqual */:
new (&this->as.ForwardSlashEqual.value) (decltype(this->as.ForwardSlashEqual.value))(move(rhs.as.ForwardSlashEqual.value));
break;
case 23 /* PercentSignEqual */:
new (&this->as.PercentSignEqual.value) (decltype(this->as.PercentSignEqual.value))(move(rhs.as.PercentSignEqual.value));
break;
case 24 /* NotEqual */:
new (&this->as.NotEqual.value) (decltype(this->as.NotEqual.value))(move(rhs.as.NotEqual.value));
break;
case 25 /* DoubleEqual */:
new (&this->as.DoubleEqual.value) (decltype(this->as.DoubleEqual.value))(move(rhs.as.DoubleEqual.value));
break;
case 26 /* GreaterThan */:
new (&this->as.GreaterThan.value) (decltype(this->as.GreaterThan.value))(move(rhs.as.GreaterThan.value));
break;
case 27 /* GreaterThanOrEqual */:
new (&this->as.GreaterThanOrEqual.value) (decltype(this->as.GreaterThanOrEqual.value))(move(rhs.as.GreaterThanOrEqual.value));
break;
case 28 /* LessThan */:
new (&this->as.LessThan.value) (decltype(this->as.LessThan.value))(move(rhs.as.LessThan.value));
break;
case 29 /* LessThanOrEqual */:
new (&this->as.LessThanOrEqual.value) (decltype(this->as.LessThanOrEqual.value))(move(rhs.as.LessThanOrEqual.value));
break;
case 30 /* LeftArithmeticShift */:
new (&this->as.LeftArithmeticShift.value) (decltype(this->as.LeftArithmeticShift.value))(move(rhs.as.LeftArithmeticShift.value));
break;
case 31 /* LeftShift */:
new (&this->as.LeftShift.value) (decltype(this->as.LeftShift.value))(move(rhs.as.LeftShift.value));
break;
case 32 /* LeftShiftEqual */:
new (&this->as.LeftShiftEqual.value) (decltype(this->as.LeftShiftEqual.value))(move(rhs.as.LeftShiftEqual.value));
break;
case 33 /* RightShift */:
new (&this->as.RightShift.value) (decltype(this->as.RightShift.value))(move(rhs.as.RightShift.value));
break;
case 34 /* RightArithmeticShift */:
new (&this->as.RightArithmeticShift.value) (decltype(this->as.RightArithmeticShift.value))(move(rhs.as.RightArithmeticShift.value));
break;
case 35 /* RightShiftEqual */:
new (&this->as.RightShiftEqual.value) (decltype(this->as.RightShiftEqual.value))(move(rhs.as.RightShiftEqual.value));
break;
case 36 /* Asterisk */:
new (&this->as.Asterisk.value) (decltype(this->as.Asterisk.value))(move(rhs.as.Asterisk.value));
break;
case 37 /* Ampersand */:
new (&this->as.Ampersand.value) (decltype(this->as.Ampersand.value))(move(rhs.as.Ampersand.value));
break;
case 38 /* AmpersandEqual */:
new (&this->as.AmpersandEqual.value) (decltype(this->as.AmpersandEqual.value))(move(rhs.as.AmpersandEqual.value));
break;
case 39 /* AmpersandAmpersand */:
new (&this->as.AmpersandAmpersand.value) (decltype(this->as.AmpersandAmpersand.value))(move(rhs.as.AmpersandAmpersand.value));
break;
case 40 /* Pipe */:
new (&this->as.Pipe.value) (decltype(this->as.Pipe.value))(move(rhs.as.Pipe.value));
break;
case 41 /* PipeEqual */:
new (&this->as.PipeEqual.value) (decltype(this->as.PipeEqual.value))(move(rhs.as.PipeEqual.value));
break;
case 42 /* PipePipe */:
new (&this->as.PipePipe.value) (decltype(this->as.PipePipe.value))(move(rhs.as.PipePipe.value));
break;
case 43 /* Caret */:
new (&this->as.Caret.value) (decltype(this->as.Caret.value))(move(rhs.as.Caret.value));
break;
case 44 /* CaretEqual */:
new (&this->as.CaretEqual.value) (decltype(this->as.CaretEqual.value))(move(rhs.as.CaretEqual.value));
break;
case 45 /* Dollar */:
new (&this->as.Dollar.value) (decltype(this->as.Dollar.value))(move(rhs.as.Dollar.value));
break;
case 46 /* Tilde */:
new (&this->as.Tilde.value) (decltype(this->as.Tilde.value))(move(rhs.as.Tilde.value));
break;
case 47 /* ForwardSlash */:
new (&this->as.ForwardSlash.value) (decltype(this->as.ForwardSlash.value))(move(rhs.as.ForwardSlash.value));
break;
case 48 /* ExclamationPoint */:
new (&this->as.ExclamationPoint.value) (decltype(this->as.ExclamationPoint.value))(move(rhs.as.ExclamationPoint.value));
break;
case 49 /* QuestionMark */:
new (&this->as.QuestionMark.value) (decltype(this->as.QuestionMark.value))(move(rhs.as.QuestionMark.value));
break;
case 50 /* QuestionMarkQuestionMark */:
new (&this->as.QuestionMarkQuestionMark.value) (decltype(this->as.QuestionMarkQuestionMark.value))(move(rhs.as.QuestionMarkQuestionMark.value));
break;
case 51 /* QuestionMarkQuestionMarkEqual */:
new (&this->as.QuestionMarkQuestionMarkEqual.value) (decltype(this->as.QuestionMarkQuestionMarkEqual.value))(move(rhs.as.QuestionMarkQuestionMarkEqual.value));
break;
case 52 /* Comma */:
new (&this->as.Comma.value) (decltype(this->as.Comma.value))(move(rhs.as.Comma.value));
break;
case 53 /* Dot */:
new (&this->as.Dot.value) (decltype(this->as.Dot.value))(move(rhs.as.Dot.value));
break;
case 54 /* DotDot */:
new (&this->as.DotDot.value) (decltype(this->as.DotDot.value))(move(rhs.as.DotDot.value));
break;
case 55 /* Eol */:
new (&this->as.Eol.comment) (decltype(this->as.Eol.comment))(move(rhs.as.Eol.comment));
new (&this->as.Eol.span) (decltype(this->as.Eol.span))(move(rhs.as.Eol.span));
break;
case 56 /* Eof */:
new (&this->as.Eof.value) (decltype(this->as.Eof.value))(move(rhs.as.Eof.value));
break;
case 57 /* FatArrow */:
new (&this->as.FatArrow.value) (decltype(this->as.FatArrow.value))(move(rhs.as.FatArrow.value));
break;
case 58 /* Arrow */:
new (&this->as.Arrow.value) (decltype(this->as.Arrow.value))(move(rhs.as.Arrow.value));
break;
case 59 /* And */:
new (&this->as.And.value) (decltype(this->as.And.value))(move(rhs.as.And.value));
break;
case 60 /* Anon */:
new (&this->as.Anon.value) (decltype(this->as.Anon.value))(move(rhs.as.Anon.value));
break;
case 61 /* As */:
new (&this->as.As.value) (decltype(this->as.As.value))(move(rhs.as.As.value));
break;
case 62 /* Boxed */:
new (&this->as.Boxed.value) (decltype(this->as.Boxed.value))(move(rhs.as.Boxed.value));
break;
case 63 /* Break */:
new (&this->as.Break.value) (decltype(this->as.Break.value))(move(rhs.as.Break.value));
break;
case 64 /* Catch */:
new (&this->as.Catch.value) (decltype(this->as.Catch.value))(move(rhs.as.Catch.value));
break;
case 65 /* Class */:
new (&this->as.Class.value) (decltype(this->as.Class.value))(move(rhs.as.Class.value));
break;
case 66 /* Continue */:
new (&this->as.Continue.value) (decltype(this->as.Continue.value))(move(rhs.as.Continue.value));
break;
case 67 /* Cpp */:
new (&this->as.Cpp.value) (decltype(this->as.Cpp.value))(move(rhs.as.Cpp.value));
break;
case 68 /* Defer */:
new (&this->as.Defer.value) (decltype(this->as.Defer.value))(move(rhs.as.Defer.value));
break;
case 69 /* Destructor */:
new (&this->as.Destructor.value) (decltype(this->as.Destructor.value))(move(rhs.as.Destructor.value));
break;
case 70 /* Else */:
new (&this->as.Else.value) (decltype(this->as.Else.value))(move(rhs.as.Else.value));
break;
case 71 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(move(rhs.as.Enum.value));
break;
case 72 /* Extern */:
new (&this->as.Extern.value) (decltype(this->as.Extern.value))(move(rhs.as.Extern.value));
break;
case 73 /* False */:
new (&this->as.False.value) (decltype(this->as.False.value))(move(rhs.as.False.value));
break;
case 74 /* For */:
new (&this->as.For.value) (decltype(this->as.For.value))(move(rhs.as.For.value));
break;
case 75 /* Fn */:
new (&this->as.Fn.value) (decltype(this->as.Fn.value))(move(rhs.as.Fn.value));
break;
case 76 /* Comptime */:
new (&this->as.Comptime.value) (decltype(this->as.Comptime.value))(move(rhs.as.Comptime.value));
break;
case 77 /* If */:
new (&this->as.If.value) (decltype(this->as.If.value))(move(rhs.as.If.value));
break;
case 78 /* Import */:
new (&this->as.Import.value) (decltype(this->as.Import.value))(move(rhs.as.Import.value));
break;
case 79 /* In */:
new (&this->as.In.value) (decltype(this->as.In.value))(move(rhs.as.In.value));
break;
case 80 /* Is */:
new (&this->as.Is.value) (decltype(this->as.Is.value))(move(rhs.as.Is.value));
break;
case 81 /* Let */:
new (&this->as.Let.value) (decltype(this->as.Let.value))(move(rhs.as.Let.value));
break;
case 82 /* Loop */:
new (&this->as.Loop.value) (decltype(this->as.Loop.value))(move(rhs.as.Loop.value));
break;
case 83 /* Match */:
new (&this->as.Match.value) (decltype(this->as.Match.value))(move(rhs.as.Match.value));
break;
case 84 /* Mut */:
new (&this->as.Mut.value) (decltype(this->as.Mut.value))(move(rhs.as.Mut.value));
break;
case 85 /* Namespace */:
new (&this->as.Namespace.value) (decltype(this->as.Namespace.value))(move(rhs.as.Namespace.value));
break;
case 86 /* Not */:
new (&this->as.Not.value) (decltype(this->as.Not.value))(move(rhs.as.Not.value));
break;
case 87 /* Or */:
new (&this->as.Or.value) (decltype(this->as.Or.value))(move(rhs.as.Or.value));
break;
case 88 /* Override */:
new (&this->as.Override.value) (decltype(this->as.Override.value))(move(rhs.as.Override.value));
break;
case 89 /* Private */:
new (&this->as.Private.value) (decltype(this->as.Private.value))(move(rhs.as.Private.value));
break;
case 90 /* Public */:
new (&this->as.Public.value) (decltype(this->as.Public.value))(move(rhs.as.Public.value));
break;
case 91 /* Raw */:
new (&this->as.Raw.value) (decltype(this->as.Raw.value))(move(rhs.as.Raw.value));
break;
case 92 /* Reflect */:
new (&this->as.Reflect.value) (decltype(this->as.Reflect.value))(move(rhs.as.Reflect.value));
break;
case 93 /* Return */:
new (&this->as.Return.value) (decltype(this->as.Return.value))(move(rhs.as.Return.value));
break;
case 94 /* Restricted */:
new (&this->as.Restricted.value) (decltype(this->as.Restricted.value))(move(rhs.as.Restricted.value));
break;
case 95 /* Sizeof */:
new (&this->as.Sizeof.value) (decltype(this->as.Sizeof.value))(move(rhs.as.Sizeof.value));
break;
case 96 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(move(rhs.as.Struct.value));
break;
case 97 /* This */:
new (&this->as.This.value) (decltype(this->as.This.value))(move(rhs.as.This.value));
break;
case 98 /* Throw */:
new (&this->as.Throw.value) (decltype(this->as.Throw.value))(move(rhs.as.Throw.value));
break;
case 99 /* Throws */:
new (&this->as.Throws.value) (decltype(this->as.Throws.value))(move(rhs.as.Throws.value));
break;
case 100 /* True */:
new (&this->as.True.value) (decltype(this->as.True.value))(move(rhs.as.True.value));
break;
case 101 /* Try */:
new (&this->as.Try.value) (decltype(this->as.Try.value))(move(rhs.as.Try.value));
break;
case 102 /* Unsafe */:
new (&this->as.Unsafe.value) (decltype(this->as.Unsafe.value))(move(rhs.as.Unsafe.value));
break;
case 103 /* Virtual */:
new (&this->as.Virtual.value) (decltype(this->as.Virtual.value))(move(rhs.as.Virtual.value));
break;
case 104 /* Weak */:
new (&this->as.Weak.value) (decltype(this->as.Weak.value))(move(rhs.as.Weak.value));
break;
case 105 /* While */:
new (&this->as.While.value) (decltype(this->as.While.value))(move(rhs.as.While.value));
break;
case 106 /* Yield */:
new (&this->as.Yield.value) (decltype(this->as.Yield.value))(move(rhs.as.Yield.value));
break;
case 107 /* Guard */:
new (&this->as.Guard.value) (decltype(this->as.Guard.value))(move(rhs.as.Guard.value));
break;
case 108 /* Implements */:
new (&this->as.Implements.value) (decltype(this->as.Implements.value))(move(rhs.as.Implements.value));
break;
case 109 /* Requires */:
new (&this->as.Requires.value) (decltype(this->as.Requires.value))(move(rhs.as.Requires.value));
break;
case 110 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(move(rhs.as.Trait.value));
break;
case 111 /* Garbage */:
new (&this->as.Garbage.consumed) (decltype(this->as.Garbage.consumed))(move(rhs.as.Garbage.consumed));
new (&this->as.Garbage.span) (decltype(this->as.Garbage.span))(move(rhs.as.Garbage.span));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
Token::~Token(){
if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant();
}
void Token::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* SingleQuotedString */:this->as.SingleQuotedString.quote.~DeprecatedString();
this->as.SingleQuotedString.prefix.~Optional();
this->as.SingleQuotedString.span.~Span();
break;
case 1 /* QuotedString */:this->as.QuotedString.quote.~DeprecatedString();
this->as.QuotedString.span.~Span();
break;
case 2 /* Number */:this->as.Number.prefix.~LiteralPrefix();
this->as.Number.number.~DeprecatedString();
this->as.Number.suffix.~LiteralSuffix();
this->as.Number.span.~Span();
break;
case 3 /* Identifier */:this->as.Identifier.name.~DeprecatedString();
this->as.Identifier.span.~Span();
break;
case 4 /* Semicolon */:this->as.Semicolon.value.~Span();
break;
case 5 /* Colon */:this->as.Colon.value.~Span();
break;
case 6 /* ColonColon */:this->as.ColonColon.value.~Span();
break;
case 7 /* LParen */:this->as.LParen.value.~Span();
break;
case 8 /* RParen */:this->as.RParen.value.~Span();
break;
case 9 /* LCurly */:this->as.LCurly.value.~Span();
break;
case 10 /* RCurly */:this->as.RCurly.value.~Span();
break;
case 11 /* LSquare */:this->as.LSquare.value.~Span();
break;
case 12 /* RSquare */:this->as.RSquare.value.~Span();
break;
case 13 /* PercentSign */:this->as.PercentSign.value.~Span();
break;
case 14 /* Plus */:this->as.Plus.value.~Span();
break;
case 15 /* Minus */:this->as.Minus.value.~Span();
break;
case 16 /* Equal */:this->as.Equal.value.~Span();
break;
case 17 /* PlusEqual */:this->as.PlusEqual.value.~Span();
break;
case 18 /* PlusPlus */:this->as.PlusPlus.value.~Span();
break;
case 19 /* MinusEqual */:this->as.MinusEqual.value.~Span();
break;
case 20 /* MinusMinus */:this->as.MinusMinus.value.~Span();
break;
case 21 /* AsteriskEqual */:this->as.AsteriskEqual.value.~Span();
break;
case 22 /* ForwardSlashEqual */:this->as.ForwardSlashEqual.value.~Span();
break;
case 23 /* PercentSignEqual */:this->as.PercentSignEqual.value.~Span();
break;
case 24 /* NotEqual */:this->as.NotEqual.value.~Span();
break;
case 25 /* DoubleEqual */:this->as.DoubleEqual.value.~Span();
break;
case 26 /* GreaterThan */:this->as.GreaterThan.value.~Span();
break;
case 27 /* GreaterThanOrEqual */:this->as.GreaterThanOrEqual.value.~Span();
break;
case 28 /* LessThan */:this->as.LessThan.value.~Span();
break;
case 29 /* LessThanOrEqual */:this->as.LessThanOrEqual.value.~Span();
break;
case 30 /* LeftArithmeticShift */:this->as.LeftArithmeticShift.value.~Span();
break;
case 31 /* LeftShift */:this->as.LeftShift.value.~Span();
break;
case 32 /* LeftShiftEqual */:this->as.LeftShiftEqual.value.~Span();
break;
case 33 /* RightShift */:this->as.RightShift.value.~Span();
break;
case 34 /* RightArithmeticShift */:this->as.RightArithmeticShift.value.~Span();
break;
case 35 /* RightShiftEqual */:this->as.RightShiftEqual.value.~Span();
break;
case 36 /* Asterisk */:this->as.Asterisk.value.~Span();
break;
case 37 /* Ampersand */:this->as.Ampersand.value.~Span();
break;
case 38 /* AmpersandEqual */:this->as.AmpersandEqual.value.~Span();
break;
case 39 /* AmpersandAmpersand */:this->as.AmpersandAmpersand.value.~Span();
break;
case 40 /* Pipe */:this->as.Pipe.value.~Span();
break;
case 41 /* PipeEqual */:this->as.PipeEqual.value.~Span();
break;
case 42 /* PipePipe */:this->as.PipePipe.value.~Span();
break;
case 43 /* Caret */:this->as.Caret.value.~Span();
break;
case 44 /* CaretEqual */:this->as.CaretEqual.value.~Span();
break;
case 45 /* Dollar */:this->as.Dollar.value.~Span();
break;
case 46 /* Tilde */:this->as.Tilde.value.~Span();
break;
case 47 /* ForwardSlash */:this->as.ForwardSlash.value.~Span();
break;
case 48 /* ExclamationPoint */:this->as.ExclamationPoint.value.~Span();
break;
case 49 /* QuestionMark */:this->as.QuestionMark.value.~Span();
break;
case 50 /* QuestionMarkQuestionMark */:this->as.QuestionMarkQuestionMark.value.~Span();
break;
case 51 /* QuestionMarkQuestionMarkEqual */:this->as.QuestionMarkQuestionMarkEqual.value.~Span();
break;
case 52 /* Comma */:this->as.Comma.value.~Span();
break;
case 53 /* Dot */:this->as.Dot.value.~Span();
break;
case 54 /* DotDot */:this->as.DotDot.value.~Span();
break;
case 55 /* Eol */:this->as.Eol.comment.~Optional();
this->as.Eol.span.~Span();
break;
case 56 /* Eof */:this->as.Eof.value.~Span();
break;
case 57 /* FatArrow */:this->as.FatArrow.value.~Span();
break;
case 58 /* Arrow */:this->as.Arrow.value.~Span();
break;
case 59 /* And */:this->as.And.value.~Span();
break;
case 60 /* Anon */:this->as.Anon.value.~Span();
break;
case 61 /* As */:this->as.As.value.~Span();
break;
case 62 /* Boxed */:this->as.Boxed.value.~Span();
break;
case 63 /* Break */:this->as.Break.value.~Span();
break;
case 64 /* Catch */:this->as.Catch.value.~Span();
break;
case 65 /* Class */:this->as.Class.value.~Span();
break;
case 66 /* Continue */:this->as.Continue.value.~Span();
break;
case 67 /* Cpp */:this->as.Cpp.value.~Span();
break;
case 68 /* Defer */:this->as.Defer.value.~Span();
break;
case 69 /* Destructor */:this->as.Destructor.value.~Span();
break;
case 70 /* Else */:this->as.Else.value.~Span();
break;
case 71 /* Enum */:this->as.Enum.value.~Span();
break;
case 72 /* Extern */:this->as.Extern.value.~Span();
break;
case 73 /* False */:this->as.False.value.~Span();
break;
case 74 /* For */:this->as.For.value.~Span();
break;
case 75 /* Fn */:this->as.Fn.value.~Span();
break;
case 76 /* Comptime */:this->as.Comptime.value.~Span();
break;
case 77 /* If */:this->as.If.value.~Span();
break;
case 78 /* Import */:this->as.Import.value.~Span();
break;
case 79 /* In */:this->as.In.value.~Span();
break;
case 80 /* Is */:this->as.Is.value.~Span();
break;
case 81 /* Let */:this->as.Let.value.~Span();
break;
case 82 /* Loop */:this->as.Loop.value.~Span();
break;
case 83 /* Match */:this->as.Match.value.~Span();
break;
case 84 /* Mut */:this->as.Mut.value.~Span();
break;
case 85 /* Namespace */:this->as.Namespace.value.~Span();
break;
case 86 /* Not */:this->as.Not.value.~Span();
break;
case 87 /* Or */:this->as.Or.value.~Span();
break;
case 88 /* Override */:this->as.Override.value.~Span();
break;
case 89 /* Private */:this->as.Private.value.~Span();
break;
case 90 /* Public */:this->as.Public.value.~Span();
break;
case 91 /* Raw */:this->as.Raw.value.~Span();
break;
case 92 /* Reflect */:this->as.Reflect.value.~Span();
break;
case 93 /* Return */:this->as.Return.value.~Span();
break;
case 94 /* Restricted */:this->as.Restricted.value.~Span();
break;
case 95 /* Sizeof */:this->as.Sizeof.value.~Span();
break;
case 96 /* Struct */:this->as.Struct.value.~Span();
break;
case 97 /* This */:this->as.This.value.~Span();
break;
case 98 /* Throw */:this->as.Throw.value.~Span();
break;
case 99 /* Throws */:this->as.Throws.value.~Span();
break;
case 100 /* True */:this->as.True.value.~Span();
break;
case 101 /* Try */:this->as.Try.value.~Span();
break;
case 102 /* Unsafe */:this->as.Unsafe.value.~Span();
break;
case 103 /* Virtual */:this->as.Virtual.value.~Span();
break;
case 104 /* Weak */:this->as.Weak.value.~Span();
break;
case 105 /* While */:this->as.While.value.~Span();
break;
case 106 /* Yield */:this->as.Yield.value.~Span();
break;
case 107 /* Guard */:this->as.Guard.value.~Span();
break;
case 108 /* Implements */:this->as.Implements.value.~Span();
break;
case 109 /* Requires */:this->as.Requires.value.~Span();
break;
case 110 /* Trait */:this->as.Trait.value.~Span();
break;
case 111 /* Garbage */:this->as.Garbage.consumed.~Optional();
this->as.Garbage.span.~Span();
break;
}
}
ErrorOr<lexer::Token> lexer::Token::from_keyword_or_identifier(DeprecatedString const string,utility::Span const span) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<lexer::Token,ErrorOr<lexer::Token>>{
auto __jakt_enum_value = (string);
if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("and"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::And(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("anon"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Anon(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("as"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::As(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("boxed"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Boxed(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("break"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Break(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("catch"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Catch(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("class"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Class(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("continue"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Continue(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("cpp"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Cpp(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("defer"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Defer(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("destructor"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Destructor(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("else"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Else(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("enum"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Enum(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("extern"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Extern(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("false"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::False(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("for"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::For(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("fn"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Fn(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("comptime"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Comptime(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("if"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::If(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("import"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Import(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("in"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::In(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("is"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Is(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("let"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Let(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("loop"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Loop(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("match"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Match(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("mut"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Mut(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("namespace"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Namespace(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("not"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Not(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("or"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Or(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("override"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Override(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("private"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Private(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("public"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Public(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("raw"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Raw(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("reflect"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Reflect(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("return"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Return(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("restricted"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Restricted(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("sizeof"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Sizeof(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("struct"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Struct(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("this"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::This(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("throw"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Throw(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("throws"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Throws(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("true"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::True(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("try"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Try(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("unsafe"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Unsafe(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("virtual"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Virtual(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("weak"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Weak(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("while"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::While(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("yield"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Yield(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("guard"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Guard(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("requires"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Requires(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("implements"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Implements(span));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("trait"sv))) {
return JaktInternal::ExplicitValue(lexer::Token::Trait(span));
}
else {
return JaktInternal::ExplicitValue(lexer::Token::Identifier(string,span));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

utility::Span lexer::Token::span() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, utility::Span>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* SingleQuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SingleQuotedString;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 2 /* Number */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Number;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4 /* Semicolon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Semicolon;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 5 /* Colon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Colon;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 6 /* ColonColon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ColonColon;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 7 /* LParen */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LParen;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 8 /* RParen */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RParen;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 9 /* LCurly */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LCurly;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 10 /* RCurly */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RCurly;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 11 /* LSquare */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LSquare;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 12 /* RSquare */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RSquare;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 13 /* PercentSign */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PercentSign;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 14 /* Plus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Plus;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 15 /* Minus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Minus;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 16 /* Equal */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Equal;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 17 /* PlusEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PlusEqual;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 18 /* PlusPlus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PlusPlus;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 19 /* MinusEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MinusEqual;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 20 /* MinusMinus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MinusMinus;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 21 /* AsteriskEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AsteriskEqual;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 22 /* ForwardSlashEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForwardSlashEqual;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 23 /* PercentSignEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PercentSignEqual;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 24 /* NotEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NotEqual;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 25 /* DoubleEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DoubleEqual;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 26 /* GreaterThan */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GreaterThan;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 27 /* GreaterThanOrEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GreaterThanOrEqual;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 28 /* LessThan */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LessThan;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 29 /* LessThanOrEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LessThanOrEqual;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 30 /* LeftArithmeticShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LeftArithmeticShift;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 31 /* LeftShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LeftShift;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 32 /* LeftShiftEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LeftShiftEqual;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 33 /* RightShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RightShift;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 34 /* RightArithmeticShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RightArithmeticShift;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 35 /* RightShiftEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RightShiftEqual;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 36 /* Asterisk */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Asterisk;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 37 /* Ampersand */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Ampersand;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 38 /* AmpersandEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AmpersandEqual;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 39 /* AmpersandAmpersand */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AmpersandAmpersand;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 40 /* Pipe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Pipe;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 41 /* PipeEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PipeEqual;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 42 /* PipePipe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PipePipe;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 43 /* Caret */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Caret;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 44 /* CaretEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CaretEqual;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 45 /* Dollar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dollar;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 46 /* Tilde */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Tilde;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 47 /* ForwardSlash */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForwardSlash;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 48 /* ExclamationPoint */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ExclamationPoint;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 49 /* QuestionMark */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuestionMark;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 50 /* QuestionMarkQuestionMark */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuestionMarkQuestionMark;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 51 /* QuestionMarkQuestionMarkEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuestionMarkQuestionMarkEqual;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 52 /* Comma */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Comma;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 53 /* Dot */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dot;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 54 /* DotDot */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DotDot;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 55 /* Eol */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Eol;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 56 /* Eof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Eof;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 57 /* FatArrow */: {
auto&& __jakt_match_value = __jakt_match_variant.as.FatArrow;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 58 /* Arrow */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Arrow;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 59 /* And */: {
auto&& __jakt_match_value = __jakt_match_variant.as.And;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 60 /* Anon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Anon;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 61 /* As */: {
auto&& __jakt_match_value = __jakt_match_variant.as.As;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 62 /* Boxed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boxed;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 63 /* Break */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Break;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 64 /* Catch */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Catch;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 65 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 66 /* Continue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Continue;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 67 /* Cpp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Cpp;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 68 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 69 /* Destructor */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Destructor;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 70 /* Else */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Else;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 71 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 72 /* Extern */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Extern;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 73 /* False */: {
auto&& __jakt_match_value = __jakt_match_variant.as.False;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 74 /* For */: {
auto&& __jakt_match_value = __jakt_match_variant.as.For;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 75 /* Fn */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Fn;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 76 /* Comptime */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Comptime;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 77 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 78 /* Import */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Import;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 79 /* In */: {
auto&& __jakt_match_value = __jakt_match_variant.as.In;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 80 /* Is */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Is;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 81 /* Let */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Let;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 82 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 83 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 84 /* Mut */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Mut;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 85 /* Namespace */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Namespace;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 86 /* Not */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Not;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 87 /* Or */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Or;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 88 /* Override */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Override;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 89 /* Private */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Private;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 90 /* Public */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Public;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 91 /* Raw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Raw;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 92 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 93 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 94 /* Restricted */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Restricted;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 95 /* Sizeof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Sizeof;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 96 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 97 /* This */: {
auto&& __jakt_match_value = __jakt_match_variant.as.This;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 98 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 99 /* Throws */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throws;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 100 /* True */: {
auto&& __jakt_match_value = __jakt_match_variant.as.True;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 101 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 102 /* Unsafe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unsafe;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 103 /* Virtual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Virtual;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 104 /* Weak */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Weak;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 105 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 106 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 107 /* Guard */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Guard;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 108 /* Implements */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Implements;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 109 /* Requires */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Requires;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 110 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 111 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<DeprecatedString> lexer::LiteralPrefix::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* None */: {
return DeprecatedString("LiteralPrefix::None"sv);
break;}
case 1 /* Hexadecimal */: {
return DeprecatedString("LiteralPrefix::Hexadecimal"sv);
break;}
case 2 /* Octal */: {
return DeprecatedString("LiteralPrefix::Octal"sv);
break;}
case 3 /* Binary */: {
return DeprecatedString("LiteralPrefix::Binary"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] LiteralPrefix LiteralPrefix::None(){
LiteralPrefix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralPrefix LiteralPrefix::Hexadecimal(){
LiteralPrefix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralPrefix LiteralPrefix::Octal(){
LiteralPrefix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
[[nodiscard]] LiteralPrefix LiteralPrefix::Binary(){
LiteralPrefix __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
return __jakt_uninit_enum;
}
LiteralPrefix& LiteralPrefix::operator=(LiteralPrefix const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* Hexadecimal */:
break;
case 2 /* Octal */:
break;
case 3 /* Binary */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* Hexadecimal */:
break;
case 2 /* Octal */:
break;
case 3 /* Binary */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
LiteralPrefix::LiteralPrefix(LiteralPrefix const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* Hexadecimal */:
break;
case 2 /* Octal */:
break;
case 3 /* Binary */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
LiteralPrefix& LiteralPrefix::operator=(LiteralPrefix &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* Hexadecimal */:
break;
case 2 /* Octal */:
break;
case 3 /* Binary */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* Hexadecimal */:
break;
case 2 /* Octal */:
break;
case 3 /* Binary */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
LiteralPrefix::LiteralPrefix(LiteralPrefix &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* Hexadecimal */:
break;
case 2 /* Octal */:
break;
case 3 /* Binary */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
LiteralPrefix::~LiteralPrefix(){
if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant();
}
void LiteralPrefix::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* None */:break;
case 1 /* Hexadecimal */:break;
case 2 /* Octal */:break;
case 3 /* Binary */:break;
}
}
ErrorOr<DeprecatedString> lexer::LiteralPrefix::to_string() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString, ErrorOr<DeprecatedString>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* None */: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(""sv)));
};/*case end*/
case 1 /* Hexadecimal */: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("0x"sv)));
};/*case end*/
case 2 /* Octal */: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("0o"sv)));
};/*case end*/
case 3 /* Binary */: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("0b"sv)));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

}
} // namespace Jakt
