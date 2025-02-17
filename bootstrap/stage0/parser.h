#pragma once
#include "__unified_forward.h"
#include "error.h"
#include "lexer.h"
#include "utility.h"
#include "compiler.h"
namespace Jakt {
namespace parser {
struct Parser {
  public:
public: size_t index;public: JaktInternal::DynamicArray<lexer::Token> tokens;public: NonnullRefPtr<compiler::Compiler> compiler;public: bool can_have_trailing_closure;public: size_t next_function_id;public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_operand_base();
public: utility::Span span(size_t const start, size_t const end) const;
public: ErrorOr<JaktInternal::Optional<parser::NumericConstant>> make_integer_numeric_constant(u64 const number, lexer::LiteralSuffix const suffix, utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedType>> parse_type_shorthand(parser::ParsedTypeQualifiers const qualifiers);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_lambda();
public: ErrorOr<NonnullRefPtr<typename parser::ParsedType>> parse_type_longhand(parser::ParsedTypeQualifiers const qualifiers);
public: ErrorOr<parser::ParsedAlias> parse_using();
public: ErrorOr<JaktInternal::DynamicArray<parser::ParsedParameter>> parse_function_parameters();
public: ErrorOr<JaktInternal::DynamicArray<parser::ParsedMatchCase>> parse_match_cases();
public: ErrorOr<JaktInternal::Optional<parser::ParsedAttribute>> parse_attribute();
public: ErrorOr<parser::ParsedMethod> parse_method(parser::FunctionLinkage const linkage, parser::Visibility const visibility, bool const is_virtual, bool const is_override, bool const is_comptime, bool const is_destructor, bool const is_unsafe);
public: ErrorOr<parser::ParsedNamespace> parse_namespace(bool const process_only_one_entity);
public: ErrorOr<JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedGenericParameter>,parser::ParsedNamespace>> parse_forall();
public: ErrorOr<parser::ParsedVarDecl> parse_variable_declaration(bool const is_mutable);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedType>> parse_type_shorthand_set(parser::ParsedTypeQualifiers const qualifiers);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedStatement>> parse_if_statement();
public: ErrorOr<JaktInternal::Optional<parser::ParsedCall>> parse_call();
public: ErrorOr<void> inject_token(lexer::Token const token);
public: ErrorOr<parser::ParsedRecord> parse_class(parser::DefinitionLinkage const definition_linkage);
public: ErrorOr<parser::ParsedExternalTraitImplementation> parse_external_trait_implementation();
public: ErrorOr<parser::ParsedMatchPattern> parse_match_pattern();
public: ErrorOr<parser::ParsedFunction> parse_function(parser::FunctionLinkage const linkage, parser::Visibility const visibility, bool const is_comptime, bool const is_destructor, bool const is_unsafe, bool const allow_missing_body);
public: ErrorOr<parser::ParsedExternImport> parse_extern_import(parser::ParsedNamespace& parent);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedType>> parse_typename();
public: ErrorOr<JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>>> parse_struct_class_body(parser::DefinitionLinkage const definition_linkage, parser::Visibility const default_visibility, bool const is_class);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_unsafe_expr();
public: static ErrorOr<parser::ParsedNamespace> parse(NonnullRefPtr<compiler::Compiler> const compiler, JaktInternal::DynamicArray<lexer::Token> const tokens);
public: ErrorOr<JaktInternal::Optional<parser::NumericConstant>> make_float_numeric_constant(f64 const number, lexer::LiteralSuffix const suffix, utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_range();
public: ErrorOr<parser::ParsedBlock> parse_fat_arrow();
public: void skip_newlines();
public: ErrorOr<JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ValueEnumVariant>,JaktInternal::DynamicArray<parser::ParsedMethod>>> parse_value_enum_body(parser::ParsedRecord const partial_enum, parser::DefinitionLinkage const definition_linkage);
public: lexer::Token previous() const;
public: ErrorOr<JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>>> parse_type_parameter_list();
public: ErrorOr<JaktInternal::DynamicArray<parser::EnumVariantPatternArgument>> parse_variant_arguments();
public: ErrorOr<NonnullRefPtr<typename parser::ParsedStatement>> parse_guard_statement();
public: bool eof() const;
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_asterisk();
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_match_expression();
public: ErrorOr<void> apply_attributes(parser::ParsedField& field, JaktInternal::DynamicArray<parser::ParsedAttribute> const& active_attributes);
public: ErrorOr<void> apply_attributes(parser::ParsedFunction& parsed_function, JaktInternal::DynamicArray<parser::ParsedAttribute> const& active_attributes);
public: ErrorOr<void> apply_attributes(parser::ParsedMethod& parsed_method, JaktInternal::DynamicArray<parser::ParsedAttribute> const& active_attributes);
public: ErrorOr<void> apply_attributes(parser::ParsedRecord& parsed_record, JaktInternal::DynamicArray<parser::ParsedAttribute> const& active_attributes);
public: lexer::Token current() const;
public: ErrorOr<parser::ParsedRecord> parse_enum(parser::DefinitionLinkage const definition_linkage, bool const is_boxed);
public: ErrorOr<parser::ParsedBlock> parse_block();
public: utility::Span empty_span() const;
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_postfix_colon_colon(utility::Span const start, NonnullRefPtr<typename parser::ParsedExpression> const expr);
public: ErrorOr<void> error(DeprecatedString const message, utility::Span const span);
public: ErrorOr<parser::ParsedTrait> parse_trait();
public: ErrorOr<parser::Visibility> parse_restricted_visibility_modifier();
public: ErrorOr<parser::ParsedVarDeclTuple> parse_destructuring_assignment(bool const is_mutable);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_operand_postfix_operator(utility::Span const start, NonnullRefPtr<typename parser::ParsedExpression> const expr);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_set_literal();
public: ErrorOr<void> parse_attribute_list(JaktInternal::DynamicArray<parser::ParsedAttribute>& active_attributes);
public: Parser(size_t a_index, JaktInternal::DynamicArray<lexer::Token> a_tokens, NonnullRefPtr<compiler::Compiler> a_compiler, bool a_can_have_trailing_closure, size_t a_next_function_id);

public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_expression(bool const allow_assignments, bool const allow_newlines);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_operator(bool const allow_assignments);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedStatement>> parse_for_statement();
public: ErrorOr<NonnullRefPtr<typename parser::ParsedType>> parse_typename_base();
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_operand();
public: ErrorOr<JaktInternal::Tuple<JaktInternal::DynamicArray<parser::SumEnumVariant>,JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>>> parse_sum_enum_body(parser::ParsedRecord const partial_enum, parser::DefinitionLinkage const definition_linkage, bool const is_boxed);
public: ErrorOr<JaktInternal::DynamicArray<parser::ParsedCapture>> parse_captures();
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_number(lexer::LiteralPrefix const prefix, DeprecatedString const number, lexer::LiteralSuffix suffix, utility::Span const span);
public: ErrorOr<parser::ParsedModuleImport> parse_module_import();
public: ErrorOr<parser::ParsedRecord> parse_record(parser::DefinitionLinkage const definition_linkage);
public: lexer::Token peek(size_t const steps) const;
public: ErrorOr<void> error_with_hint(DeprecatedString const message, utility::Span const span, DeprecatedString const hint, utility::Span const hint_span);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedType>> parse_type_shorthand_array_or_dictionary(parser::ParsedTypeQualifiers const qualifiers);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedType>> parse_type_shorthand_tuple(parser::ParsedTypeQualifiers const qualifiers);
public: bool eol() const;
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_array_or_dictionary_literal();
public: ErrorOr<JaktInternal::DynamicArray<parser::ParsedMatchPattern>> parse_match_patterns();
public: ErrorOr<void> parse_import(parser::ParsedNamespace& parent);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedStatement>> parse_statement(bool const inside_block);
public: ErrorOr<parser::ParsedField> parse_field(parser::Visibility const visibility);
public: ErrorOr<DeprecatedString> parse_argument_label();
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_ampersand();
public: ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<parser::IncludeAction>>> parse_include_action();
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_try_block();
public: ErrorOr<JaktInternal::DynamicArray<parser::ParsedGenericParameter>> parse_generic_parameters();
public: ErrorOr<parser::ParsedRecord> parse_struct(parser::DefinitionLinkage const definition_linkage);
public: ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters>>> parse_trait_list();
public: ErrorOr<DeprecatedString> debug_description() const;
};struct ImportName {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
DeprecatedString name;
utility::Span span;
} Literal;
struct {
NonnullRefPtr<typename parser::ParsedExpression> expression;
} Comptime;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static ImportName Literal(DeprecatedString name, utility::Span span);
[[nodiscard]] static ImportName Comptime(NonnullRefPtr<typename parser::ParsedExpression> expression);
~ImportName();
ImportName& operator=(ImportName const &);
ImportName& operator=(ImportName &&);
ImportName(ImportName const&);
ImportName(ImportName &&);
private: void __jakt_destroy_variant();
public:
ErrorOr<DeprecatedString> literal_name() const;
bool equals(parser::ImportName const other) const;
utility::Span span() const;
private:
ImportName() {};
};
struct ExternalName {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
DeprecatedString value;
} Plain;
struct {
DeprecatedString value;
} PreprocessorName;
struct {
DeprecatedString name;
bool is_prefix;
} Operator;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static ExternalName Plain(DeprecatedString value);
[[nodiscard]] static ExternalName PreprocessorName(DeprecatedString value);
[[nodiscard]] static ExternalName Operator(DeprecatedString name, bool is_prefix);
~ExternalName();
ExternalName& operator=(ExternalName const &);
ExternalName& operator=(ExternalName &&);
ExternalName(ExternalName const&);
ExternalName(ExternalName &&);
private: void __jakt_destroy_variant();
public:
ErrorOr<DeprecatedString> as_name_for_use() const;
bool is_scopable() const;
bool is_prefix() const;
ErrorOr<DeprecatedString> as_name_for_definition() const;
private:
ExternalName() {};
};
struct ParsedVarDecl {
  public:
public: DeprecatedString name;public: NonnullRefPtr<typename parser::ParsedType> parsed_type;public: bool is_mutable;public: JaktInternal::Optional<utility::Span> inlay_span;public: utility::Span span;public: JaktInternal::Optional<parser::ExternalName> external_name;public: bool equals(parser::ParsedVarDecl const rhs_var_decl) const;
public: ParsedVarDecl(DeprecatedString a_name, NonnullRefPtr<typename parser::ParsedType> a_parsed_type, bool a_is_mutable, JaktInternal::Optional<utility::Span> a_inlay_span, utility::Span a_span, JaktInternal::Optional<parser::ExternalName> a_external_name);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct Visibility {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
JaktInternal::DynamicArray<parser::VisibilityRestriction> whitelist;
utility::Span span;
} Restricted;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static Visibility Public();
[[nodiscard]] static Visibility Private();
[[nodiscard]] static Visibility Restricted(JaktInternal::DynamicArray<parser::VisibilityRestriction> whitelist, utility::Span span);
~Visibility();
Visibility& operator=(Visibility const &);
Visibility& operator=(Visibility &&);
Visibility(Visibility const&);
Visibility(Visibility &&);
private: void __jakt_destroy_variant();
public:
private:
Visibility() {};
};
struct ParsedField {
  public:
public: parser::ParsedVarDecl var_decl;public: parser::Visibility visibility;public: JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> default_value;public: ParsedField(parser::ParsedVarDecl a_var_decl, parser::Visibility a_visibility, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> a_default_value);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct SumEnumVariant {
  public:
public: DeprecatedString name;public: utility::Span span;public: JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedVarDecl>> params;public: JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>>>> default_values;public: SumEnumVariant(DeprecatedString a_name, utility::Span a_span, JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedVarDecl>> a_params, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>>>> a_default_values);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedBlock {
  public:
public: JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedStatement>> stmts;public: ParsedBlock(JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedStatement>> a_stmts);

public: JaktInternal::Optional<utility::Span> find_yield_span() const;
public: bool equals(parser::ParsedBlock const rhs_block) const;
public: ErrorOr<JaktInternal::Optional<utility::Span>> span(parser::Parser const parser) const;
public: JaktInternal::Optional<utility::Span> find_yield_keyword_span() const;
public: ErrorOr<DeprecatedString> debug_description() const;
};struct FunctionType {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static FunctionType Normal();
[[nodiscard]] static FunctionType Destructor();
[[nodiscard]] static FunctionType ImplicitConstructor();
[[nodiscard]] static FunctionType ImplicitEnumConstructor();
[[nodiscard]] static FunctionType ExternalClassConstructor();
[[nodiscard]] static FunctionType Expression();
[[nodiscard]] static FunctionType Closure();
~FunctionType();
FunctionType& operator=(FunctionType const &);
FunctionType& operator=(FunctionType &&);
FunctionType(FunctionType const&);
FunctionType(FunctionType &&);
private: void __jakt_destroy_variant();
public:
private:
FunctionType() {};
};
struct FunctionLinkage {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static FunctionLinkage Internal();
[[nodiscard]] static FunctionLinkage External();
~FunctionLinkage();
FunctionLinkage& operator=(FunctionLinkage const &);
FunctionLinkage& operator=(FunctionLinkage &&);
FunctionLinkage(FunctionLinkage const&);
FunctionLinkage(FunctionLinkage &&);
private: void __jakt_destroy_variant();
public:
private:
FunctionLinkage() {};
};
struct InlineState {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static InlineState Default();
[[nodiscard]] static InlineState MakeDefinitionAvailable();
[[nodiscard]] static InlineState ForceInline();
~InlineState();
InlineState& operator=(InlineState const &);
InlineState& operator=(InlineState &&);
InlineState(InlineState const&);
InlineState(InlineState &&);
private: void __jakt_destroy_variant();
public:
private:
InlineState() {};
};
struct ParsedFunction {
  public:
public: size_t id;public: DeprecatedString name;public: utility::Span name_span;public: parser::Visibility visibility;public: JaktInternal::DynamicArray<parser::ParsedParameter> params;public: JaktInternal::DynamicArray<parser::ParsedGenericParameter> generic_parameters;public: parser::ParsedBlock block;public: NonnullRefPtr<typename parser::ParsedType> return_type;public: utility::Span return_type_span;public: bool can_throw;public: parser::FunctionType type;public: parser::FunctionLinkage linkage;public: bool must_instantiate;public: bool is_comptime;public: bool is_fat_arrow;public: bool is_unsafe;public: JaktInternal::Optional<parser::ExternalName> external_name;public: JaktInternal::Optional<DeprecatedString> deprecated_message;public: JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>>> stores_arguments;public: parser::InlineState force_inline;public: ParsedFunction(size_t a_id, DeprecatedString a_name, utility::Span a_name_span, parser::Visibility a_visibility, JaktInternal::DynamicArray<parser::ParsedParameter> a_params, JaktInternal::DynamicArray<parser::ParsedGenericParameter> a_generic_parameters, parser::ParsedBlock a_block, NonnullRefPtr<typename parser::ParsedType> a_return_type, utility::Span a_return_type_span, bool a_can_throw, parser::FunctionType a_type, parser::FunctionLinkage a_linkage, bool a_must_instantiate, bool a_is_comptime, bool a_is_fat_arrow, bool a_is_unsafe, JaktInternal::Optional<parser::ExternalName> a_external_name, JaktInternal::Optional<DeprecatedString> a_deprecated_message, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>>> a_stores_arguments, parser::InlineState a_force_inline);

public: bool equals(parser::ParsedFunction const other, bool const ignore_block) const;
public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedMethod {
  public:
public: parser::ParsedFunction parsed_function;public: parser::Visibility visibility;public: bool is_virtual;public: bool is_override;public: ParsedMethod(parser::ParsedFunction a_parsed_function, parser::Visibility a_visibility, bool a_is_virtual, bool a_is_override);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedTraitRequirements {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
JaktInternal::DynamicArray<parser::ParsedFunction> value;
} Methods;
struct {
NonnullRefPtr<typename parser::ParsedExpression> value;
} ComptimeExpression;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static ParsedTraitRequirements Nothing();
[[nodiscard]] static ParsedTraitRequirements Methods(JaktInternal::DynamicArray<parser::ParsedFunction> value);
[[nodiscard]] static ParsedTraitRequirements ComptimeExpression(NonnullRefPtr<typename parser::ParsedExpression> value);
~ParsedTraitRequirements();
ParsedTraitRequirements& operator=(ParsedTraitRequirements const &);
ParsedTraitRequirements& operator=(ParsedTraitRequirements &&);
ParsedTraitRequirements(ParsedTraitRequirements const&);
ParsedTraitRequirements(ParsedTraitRequirements &&);
private: void __jakt_destroy_variant();
public:
private:
ParsedTraitRequirements() {};
};
struct DefinitionLinkage {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static DefinitionLinkage Internal();
[[nodiscard]] static DefinitionLinkage External();
~DefinitionLinkage();
DefinitionLinkage& operator=(DefinitionLinkage const &);
DefinitionLinkage& operator=(DefinitionLinkage &&);
DefinitionLinkage(DefinitionLinkage const&);
DefinitionLinkage(DefinitionLinkage &&);
private: void __jakt_destroy_variant();
public:
private:
DefinitionLinkage() {};
};
struct TypeCast {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
NonnullRefPtr<typename parser::ParsedType> value;
} Fallible;
struct {
NonnullRefPtr<typename parser::ParsedType> value;
} Infallible;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static TypeCast Fallible(NonnullRefPtr<typename parser::ParsedType> value);
[[nodiscard]] static TypeCast Infallible(NonnullRefPtr<typename parser::ParsedType> value);
~TypeCast();
TypeCast& operator=(TypeCast const &);
TypeCast& operator=(TypeCast &&);
TypeCast(TypeCast const&);
TypeCast(TypeCast &&);
private: void __jakt_destroy_variant();
public:
NonnullRefPtr<typename parser::ParsedType> parsed_type() const;
private:
TypeCast() {};
};
struct UnaryOperator {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
parser::TypeCast value;
} TypeCast;
struct {
NonnullRefPtr<typename parser::ParsedType> value;
} Is;
struct {
NonnullRefPtr<typename parser::ParsedType> inner;
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> bindings;
} IsEnumVariant;
struct {
NonnullRefPtr<typename parser::ParsedType> value;
} Sizeof;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static UnaryOperator PreIncrement();
[[nodiscard]] static UnaryOperator PostIncrement();
[[nodiscard]] static UnaryOperator PreDecrement();
[[nodiscard]] static UnaryOperator PostDecrement();
[[nodiscard]] static UnaryOperator Negate();
[[nodiscard]] static UnaryOperator Dereference();
[[nodiscard]] static UnaryOperator RawAddress();
[[nodiscard]] static UnaryOperator Reference();
[[nodiscard]] static UnaryOperator MutableReference();
[[nodiscard]] static UnaryOperator LogicalNot();
[[nodiscard]] static UnaryOperator BitwiseNot();
[[nodiscard]] static UnaryOperator TypeCast(parser::TypeCast value);
[[nodiscard]] static UnaryOperator Is(NonnullRefPtr<typename parser::ParsedType> value);
[[nodiscard]] static UnaryOperator IsEnumVariant(NonnullRefPtr<typename parser::ParsedType> inner, JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> bindings);
[[nodiscard]] static UnaryOperator Sizeof(NonnullRefPtr<typename parser::ParsedType> value);
~UnaryOperator();
UnaryOperator& operator=(UnaryOperator const &);
UnaryOperator& operator=(UnaryOperator &&);
UnaryOperator(UnaryOperator const&);
UnaryOperator(UnaryOperator &&);
private: void __jakt_destroy_variant();
public:
bool equals(parser::UnaryOperator const rhs_op) const;
private:
UnaryOperator() {};
};
struct ParsedCapture {
u8 __jakt_variant_index = 0;
union CommonData {
u8 __jakt_uninit_common;
struct {
DeprecatedString name;
utility::Span span;
} init_common;
constexpr CommonData() {}
~CommonData() {}
} common;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static ParsedCapture ByValue(DeprecatedString name, utility::Span span);
[[nodiscard]] static ParsedCapture ByReference(DeprecatedString name, utility::Span span);
[[nodiscard]] static ParsedCapture ByMutableReference(DeprecatedString name, utility::Span span);
[[nodiscard]] static ParsedCapture ByComptimeDependency(DeprecatedString name, utility::Span span);
[[nodiscard]] static ParsedCapture AllByReference(DeprecatedString name, utility::Span span);
~ParsedCapture();
ParsedCapture& operator=(ParsedCapture const &);
ParsedCapture& operator=(ParsedCapture &&);
ParsedCapture(ParsedCapture const&);
ParsedCapture(ParsedCapture &&);
private: void __jakt_destroy_variant();
public:
private:
ParsedCapture() {};
};
struct VisibilityRestriction {
  public:
public: JaktInternal::DynamicArray<DeprecatedString> namespace_;public: DeprecatedString name;public: VisibilityRestriction(JaktInternal::DynamicArray<DeprecatedString> a_namespace_, DeprecatedString a_name);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct IncludeAction {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
DeprecatedString name;
utility::Span span;
DeprecatedString value;
} Define;
struct {
DeprecatedString name;
utility::Span span;
} Undefine;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static IncludeAction Define(DeprecatedString name, utility::Span span, DeprecatedString value);
[[nodiscard]] static IncludeAction Undefine(DeprecatedString name, utility::Span span);
~IncludeAction();
IncludeAction& operator=(IncludeAction const &);
IncludeAction& operator=(IncludeAction &&);
IncludeAction(IncludeAction const&);
IncludeAction(IncludeAction &&);
private: void __jakt_destroy_variant();
public:
private:
IncludeAction() {};
};
struct ParsedMatchPattern {
u8 __jakt_variant_index = 0;
union CommonData {
u8 __jakt_uninit_common;
struct {
JaktInternal::Dictionary<DeprecatedString,parser::ParsedPatternDefault> defaults;
} init_common;
constexpr CommonData() {}
~CommonData() {}
} common;
union VariantData {
u8 __jakt_uninit_value;
struct {
JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>> variant_names;
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> variant_arguments;
utility::Span arguments_span;
} EnumVariant;
struct {
NonnullRefPtr<typename parser::ParsedExpression> value;
} Expression;
struct {
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> variant_arguments;
utility::Span arguments_span;
} CatchAll;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static ParsedMatchPattern EnumVariant(JaktInternal::Dictionary<DeprecatedString,parser::ParsedPatternDefault> defaults, JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>> variant_names, JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> variant_arguments, utility::Span arguments_span);
[[nodiscard]] static ParsedMatchPattern Expression(JaktInternal::Dictionary<DeprecatedString,parser::ParsedPatternDefault> defaults, NonnullRefPtr<typename parser::ParsedExpression> value);
[[nodiscard]] static ParsedMatchPattern CatchAll(JaktInternal::Dictionary<DeprecatedString,parser::ParsedPatternDefault> defaults, JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> variant_arguments, utility::Span arguments_span);
[[nodiscard]] static ParsedMatchPattern Invalid(JaktInternal::Dictionary<DeprecatedString,parser::ParsedPatternDefault> defaults);
~ParsedMatchPattern();
ParsedMatchPattern& operator=(ParsedMatchPattern const &);
ParsedMatchPattern& operator=(ParsedMatchPattern &&);
ParsedMatchPattern(ParsedMatchPattern const&);
ParsedMatchPattern(ParsedMatchPattern &&);
private: void __jakt_destroy_variant();
public:
bool equals(parser::ParsedMatchPattern const rhs_parsed_match_pattern) const;
bool is_equal_pattern(parser::ParsedMatchPattern const rhs_parsed_match_pattern) const;
bool defaults_equal(JaktInternal::Dictionary<DeprecatedString,parser::ParsedPatternDefault> const defaults) const;
private:
ParsedMatchPattern() {};
};
struct CheckedQualifiers {
  public:
public: bool is_immutable;public: bool equals(parser::CheckedQualifiers const other) const;
public: CheckedQualifiers(bool a_is_immutable);

public: public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedExternalTraitImplementation {
  public:
public: NonnullRefPtr<typename parser::ParsedType> for_type;public: JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters> traits;public: JaktInternal::DynamicArray<parser::ParsedMethod> methods;public: ParsedExternalTraitImplementation(NonnullRefPtr<typename parser::ParsedType> a_for_type, JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters> a_traits, JaktInternal::DynamicArray<parser::ParsedMethod> a_methods);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedPatternDefault {
  public:
public: parser::ParsedVarDecl variable;public: NonnullRefPtr<typename parser::ParsedExpression> value;public: ParsedPatternDefault(parser::ParsedVarDecl a_variable, NonnullRefPtr<typename parser::ParsedExpression> a_value);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedMatchBody {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
NonnullRefPtr<typename parser::ParsedExpression> value;
} Expression;
struct {
parser::ParsedBlock value;
} Block;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static ParsedMatchBody Expression(NonnullRefPtr<typename parser::ParsedExpression> value);
[[nodiscard]] static ParsedMatchBody Block(parser::ParsedBlock value);
~ParsedMatchBody();
ParsedMatchBody& operator=(ParsedMatchBody const &);
ParsedMatchBody& operator=(ParsedMatchBody &&);
ParsedMatchBody(ParsedMatchBody const&);
ParsedMatchBody(ParsedMatchBody &&);
private: void __jakt_destroy_variant();
public:
bool equals(parser::ParsedMatchBody const rhs_match_body) const;
private:
ParsedMatchBody() {};
};
struct NumericConstant {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
i8 value;
} I8;
struct {
i16 value;
} I16;
struct {
i32 value;
} I32;
struct {
i64 value;
} I64;
struct {
u8 value;
} U8;
struct {
u16 value;
} U16;
struct {
u32 value;
} U32;
struct {
u64 value;
} U64;
struct {
u64 value;
} USize;
struct {
f32 value;
} F32;
struct {
f64 value;
} F64;
struct {
i64 value;
} UnknownSigned;
struct {
u64 value;
} UnknownUnsigned;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static NumericConstant I8(i8 value);
[[nodiscard]] static NumericConstant I16(i16 value);
[[nodiscard]] static NumericConstant I32(i32 value);
[[nodiscard]] static NumericConstant I64(i64 value);
[[nodiscard]] static NumericConstant U8(u8 value);
[[nodiscard]] static NumericConstant U16(u16 value);
[[nodiscard]] static NumericConstant U32(u32 value);
[[nodiscard]] static NumericConstant U64(u64 value);
[[nodiscard]] static NumericConstant USize(u64 value);
[[nodiscard]] static NumericConstant F32(f32 value);
[[nodiscard]] static NumericConstant F64(f64 value);
[[nodiscard]] static NumericConstant UnknownSigned(i64 value);
[[nodiscard]] static NumericConstant UnknownUnsigned(u64 value);
~NumericConstant();
NumericConstant& operator=(NumericConstant const &);
NumericConstant& operator=(NumericConstant &&);
NumericConstant(NumericConstant const&);
NumericConstant(NumericConstant &&);
private: void __jakt_destroy_variant();
public:
size_t to_usize() const;
private:
NumericConstant() {};
};
struct ParsedCall {
  public:
public: JaktInternal::DynamicArray<DeprecatedString> namespace_;public: DeprecatedString name;public: JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> args;public: JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> type_args;public: ParsedCall(JaktInternal::DynamicArray<DeprecatedString> a_namespace_, DeprecatedString a_name, JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> a_args, JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> a_type_args);

public: bool equals(parser::ParsedCall const rhs_parsed_call) const;
public: ErrorOr<DeprecatedString> debug_description() const;
};struct BinaryOperator {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static BinaryOperator Add();
[[nodiscard]] static BinaryOperator Subtract();
[[nodiscard]] static BinaryOperator Multiply();
[[nodiscard]] static BinaryOperator Divide();
[[nodiscard]] static BinaryOperator Modulo();
[[nodiscard]] static BinaryOperator LessThan();
[[nodiscard]] static BinaryOperator LessThanOrEqual();
[[nodiscard]] static BinaryOperator GreaterThan();
[[nodiscard]] static BinaryOperator GreaterThanOrEqual();
[[nodiscard]] static BinaryOperator Equal();
[[nodiscard]] static BinaryOperator NotEqual();
[[nodiscard]] static BinaryOperator BitwiseAnd();
[[nodiscard]] static BinaryOperator BitwiseXor();
[[nodiscard]] static BinaryOperator BitwiseOr();
[[nodiscard]] static BinaryOperator BitwiseLeftShift();
[[nodiscard]] static BinaryOperator BitwiseRightShift();
[[nodiscard]] static BinaryOperator ArithmeticLeftShift();
[[nodiscard]] static BinaryOperator ArithmeticRightShift();
[[nodiscard]] static BinaryOperator LogicalAnd();
[[nodiscard]] static BinaryOperator LogicalOr();
[[nodiscard]] static BinaryOperator NoneCoalescing();
[[nodiscard]] static BinaryOperator Assign();
[[nodiscard]] static BinaryOperator BitwiseAndAssign();
[[nodiscard]] static BinaryOperator BitwiseOrAssign();
[[nodiscard]] static BinaryOperator BitwiseXorAssign();
[[nodiscard]] static BinaryOperator BitwiseLeftShiftAssign();
[[nodiscard]] static BinaryOperator BitwiseRightShiftAssign();
[[nodiscard]] static BinaryOperator AddAssign();
[[nodiscard]] static BinaryOperator SubtractAssign();
[[nodiscard]] static BinaryOperator MultiplyAssign();
[[nodiscard]] static BinaryOperator ModuloAssign();
[[nodiscard]] static BinaryOperator DivideAssign();
[[nodiscard]] static BinaryOperator NoneCoalescingAssign();
[[nodiscard]] static BinaryOperator Garbage();
~BinaryOperator();
BinaryOperator& operator=(BinaryOperator const &);
BinaryOperator& operator=(BinaryOperator &&);
BinaryOperator(BinaryOperator const&);
BinaryOperator(BinaryOperator &&);
private: void __jakt_destroy_variant();
public:
bool equals(parser::BinaryOperator const rhs_op) const;
bool is_assignment() const;
private:
BinaryOperator() {};
};
struct EnumVariantPatternArgument {
  public:
public: JaktInternal::Optional<DeprecatedString> name;public: JaktInternal::Optional<utility::Span> name_span;public: DeprecatedString binding;public: utility::Span span;public: bool is_reference;public: bool is_mutable;public: utility::Span name_in_enum_span() const;
public: DeprecatedString name_in_enum() const;
public: EnumVariantPatternArgument(JaktInternal::Optional<DeprecatedString> a_name, JaktInternal::Optional<utility::Span> a_name_span, DeprecatedString a_binding, utility::Span a_span, bool a_is_reference, bool a_is_mutable);

public: bool equals(parser::EnumVariantPatternArgument const rhs_variant_pattern_argument) const;
public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedExpression: public RefCounted<ParsedExpression> {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
bool val;
utility::Span span;
} Boolean;
struct {
parser::NumericConstant val;
utility::Span span;
} NumericConstant;
struct {
DeprecatedString val;
utility::Span span;
} QuotedString;
struct {
DeprecatedString val;
JaktInternal::Optional<DeprecatedString> prefix;
utility::Span span;
} SingleQuotedString;
struct {
parser::ParsedCall call;
utility::Span span;
} Call;
struct {
NonnullRefPtr<typename parser::ParsedExpression> expr;
parser::ParsedCall call;
bool is_optional;
utility::Span span;
} MethodCall;
struct {
NonnullRefPtr<typename parser::ParsedExpression> expr;
size_t index;
bool is_optional;
utility::Span span;
} IndexedTuple;
struct {
NonnullRefPtr<typename parser::ParsedExpression> expr;
DeprecatedString field_name;
bool is_optional;
utility::Span span;
} IndexedStruct;
struct {
NonnullRefPtr<typename parser::ParsedExpression> expr;
NonnullRefPtr<typename parser::ParsedExpression> index;
bool is_optional;
utility::Span span;
} ComptimeIndex;
struct {
DeprecatedString name;
utility::Span span;
} Var;
struct {
NonnullRefPtr<typename parser::ParsedExpression> base;
NonnullRefPtr<typename parser::ParsedExpression> index;
utility::Span span;
} IndexedExpression;
struct {
NonnullRefPtr<typename parser::ParsedExpression> expr;
parser::UnaryOperator op;
utility::Span span;
} UnaryOp;
struct {
NonnullRefPtr<typename parser::ParsedExpression> lhs;
parser::BinaryOperator op;
NonnullRefPtr<typename parser::ParsedExpression> rhs;
utility::Span span;
} BinaryOp;
struct {
parser::BinaryOperator op;
utility::Span span;
} Operator;
struct {
NonnullRefPtr<typename parser::ParsedExpression> expr;
utility::Span span;
} OptionalSome;
struct {
utility::Span value;
} OptionalNone;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> values;
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> fill_size;
utility::Span span;
} JaktArray;
struct {
JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>>> values;
utility::Span span;
} JaktDictionary;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> values;
utility::Span span;
} Set;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> values;
utility::Span span;
} JaktTuple;
struct {
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> from;
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> to;
utility::Span span;
} Range;
struct {
NonnullRefPtr<typename parser::ParsedExpression> expr;
utility::Span span;
} ForcedUnwrap;
struct {
NonnullRefPtr<typename parser::ParsedExpression> expr;
JaktInternal::DynamicArray<parser::ParsedMatchCase> cases;
utility::Span span;
utility::Span marker_span;
} Match;
struct {
NonnullRefPtr<typename parser::ParsedExpression> expr;
parser::EnumVariantPatternArgument arg;
NonnullRefPtr<typename parser::ParsedType> enum_variant;
utility::Span span;
} EnumVariantArg;
struct {
DeprecatedString name;
JaktInternal::DynamicArray<DeprecatedString> namespace_;
utility::Span span;
} NamespacedVar;
struct {
JaktInternal::DynamicArray<parser::ParsedCapture> captures;
JaktInternal::DynamicArray<parser::ParsedParameter> params;
bool can_throw;
bool is_fat_arrow;
NonnullRefPtr<typename parser::ParsedType> return_type;
parser::ParsedBlock block;
utility::Span span;
} Function;
struct {
NonnullRefPtr<typename parser::ParsedExpression> expr;
JaktInternal::Optional<parser::ParsedBlock> catch_block;
JaktInternal::Optional<utility::Span> catch_span;
JaktInternal::Optional<DeprecatedString> catch_name;
utility::Span span;
} Try;
struct {
NonnullRefPtr<typename parser::ParsedStatement> stmt;
DeprecatedString error_name;
utility::Span error_span;
parser::ParsedBlock catch_block;
utility::Span span;
} TryBlock;
struct {
NonnullRefPtr<typename parser::ParsedType> type;
utility::Span span;
} Reflect;
struct {
utility::Span value;
} Garbage;
struct {
NonnullRefPtr<typename parser::ParsedExpression> expr;
utility::Span span;
} Unsafe;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> Boolean(bool val, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> NumericConstant(parser::NumericConstant val, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> QuotedString(DeprecatedString val, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> SingleQuotedString(DeprecatedString val, JaktInternal::Optional<DeprecatedString> prefix, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> Call(parser::ParsedCall call, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> MethodCall(NonnullRefPtr<typename parser::ParsedExpression> expr, parser::ParsedCall call, bool is_optional, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> IndexedTuple(NonnullRefPtr<typename parser::ParsedExpression> expr, size_t index, bool is_optional, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> IndexedStruct(NonnullRefPtr<typename parser::ParsedExpression> expr, DeprecatedString field_name, bool is_optional, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> ComptimeIndex(NonnullRefPtr<typename parser::ParsedExpression> expr, NonnullRefPtr<typename parser::ParsedExpression> index, bool is_optional, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> Var(DeprecatedString name, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> IndexedExpression(NonnullRefPtr<typename parser::ParsedExpression> base, NonnullRefPtr<typename parser::ParsedExpression> index, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> UnaryOp(NonnullRefPtr<typename parser::ParsedExpression> expr, parser::UnaryOperator op, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> BinaryOp(NonnullRefPtr<typename parser::ParsedExpression> lhs, parser::BinaryOperator op, NonnullRefPtr<typename parser::ParsedExpression> rhs, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> Operator(parser::BinaryOperator op, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> OptionalSome(NonnullRefPtr<typename parser::ParsedExpression> expr, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> OptionalNone(utility::Span value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> JaktArray(JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> values, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> fill_size, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> JaktDictionary(JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>>> values, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> Set(JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> values, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> JaktTuple(JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> values, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> Range(JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> from, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> to, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> ForcedUnwrap(NonnullRefPtr<typename parser::ParsedExpression> expr, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> Match(NonnullRefPtr<typename parser::ParsedExpression> expr, JaktInternal::DynamicArray<parser::ParsedMatchCase> cases, utility::Span span, utility::Span marker_span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> EnumVariantArg(NonnullRefPtr<typename parser::ParsedExpression> expr, parser::EnumVariantPatternArgument arg, NonnullRefPtr<typename parser::ParsedType> enum_variant, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> NamespacedVar(DeprecatedString name, JaktInternal::DynamicArray<DeprecatedString> namespace_, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> Function(JaktInternal::DynamicArray<parser::ParsedCapture> captures, JaktInternal::DynamicArray<parser::ParsedParameter> params, bool can_throw, bool is_fat_arrow, NonnullRefPtr<typename parser::ParsedType> return_type, parser::ParsedBlock block, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> Try(NonnullRefPtr<typename parser::ParsedExpression> expr, JaktInternal::Optional<parser::ParsedBlock> catch_block, JaktInternal::Optional<utility::Span> catch_span, JaktInternal::Optional<DeprecatedString> catch_name, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> TryBlock(NonnullRefPtr<typename parser::ParsedStatement> stmt, DeprecatedString error_name, utility::Span error_span, parser::ParsedBlock catch_block, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> Reflect(NonnullRefPtr<typename parser::ParsedType> type, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> Garbage(utility::Span value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedExpression>> Unsafe(NonnullRefPtr<typename parser::ParsedExpression> expr, utility::Span span);
~ParsedExpression();
ParsedExpression& operator=(ParsedExpression const &);
ParsedExpression& operator=(ParsedExpression &&);
ParsedExpression(ParsedExpression const&);
ParsedExpression(ParsedExpression &&);
private: void __jakt_destroy_variant();
public:
bool equals(NonnullRefPtr<typename parser::ParsedExpression> const rhs_expression) const;
utility::Span span() const;
i64 precedence() const;
private:
ParsedExpression() {};
};
struct ParsedAttributeArgument {
  public:
public: DeprecatedString name;public: utility::Span span;public: JaktInternal::Optional<DeprecatedString> assigned_value;public: ParsedAttributeArgument(DeprecatedString a_name, utility::Span a_span, JaktInternal::Optional<DeprecatedString> a_assigned_value);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedVariable {
  public:
public: DeprecatedString name;public: NonnullRefPtr<typename parser::ParsedType> parsed_type;public: bool is_mutable;public: utility::Span span;public: ParsedVariable(DeprecatedString a_name, NonnullRefPtr<typename parser::ParsedType> a_parsed_type, bool a_is_mutable, utility::Span a_span);

public: bool equals(parser::ParsedVariable const rhs_parsed_varible) const;
public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedTypeQualifiers {
  public:
public: bool is_mutable;public: bool is_immutable;public: ParsedTypeQualifiers(bool a_is_mutable, bool a_is_immutable);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedNamespace {
  public:
public: JaktInternal::Optional<DeprecatedString> name;public: JaktInternal::Optional<utility::Span> name_span;public: JaktInternal::DynamicArray<parser::ParsedFunction> functions;public: JaktInternal::DynamicArray<parser::ParsedRecord> records;public: JaktInternal::DynamicArray<parser::ParsedTrait> traits;public: JaktInternal::DynamicArray<parser::ParsedExternalTraitImplementation> external_trait_implementations;public: JaktInternal::DynamicArray<parser::ParsedNamespace> namespaces;public: JaktInternal::DynamicArray<parser::ParsedAlias> aliases;public: JaktInternal::DynamicArray<parser::ParsedModuleImport> module_imports;public: JaktInternal::DynamicArray<parser::ParsedExternImport> extern_imports;public: JaktInternal::Optional<DeprecatedString> import_path_if_extern;public: JaktInternal::DynamicArray<parser::IncludeAction> generating_import_extern_before_include;public: JaktInternal::DynamicArray<parser::IncludeAction> generating_import_extern_after_include;public: JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedGenericParameter>,parser::ParsedNamespace>> forall_chunks;public: ErrorOr<void> add_child_namespace(parser::ParsedNamespace const namespace_);
public: ParsedNamespace(JaktInternal::Optional<DeprecatedString> a_name, JaktInternal::Optional<utility::Span> a_name_span, JaktInternal::DynamicArray<parser::ParsedFunction> a_functions, JaktInternal::DynamicArray<parser::ParsedRecord> a_records, JaktInternal::DynamicArray<parser::ParsedTrait> a_traits, JaktInternal::DynamicArray<parser::ParsedExternalTraitImplementation> a_external_trait_implementations, JaktInternal::DynamicArray<parser::ParsedNamespace> a_namespaces, JaktInternal::DynamicArray<parser::ParsedAlias> a_aliases, JaktInternal::DynamicArray<parser::ParsedModuleImport> a_module_imports, JaktInternal::DynamicArray<parser::ParsedExternImport> a_extern_imports, JaktInternal::Optional<DeprecatedString> a_import_path_if_extern, JaktInternal::DynamicArray<parser::IncludeAction> a_generating_import_extern_before_include, JaktInternal::DynamicArray<parser::IncludeAction> a_generating_import_extern_after_include, JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedGenericParameter>,parser::ParsedNamespace>> a_forall_chunks);

public: bool is_equivalent_to(parser::ParsedNamespace const other) const;
public: ErrorOr<void> add_extern_import(parser::ParsedExternImport const import_);
public: ErrorOr<void> add_alias(parser::ParsedAlias const alias);
public: ErrorOr<void> merge_with(parser::ParsedNamespace const namespace_);
public: ErrorOr<void> add_module_import(parser::ParsedModuleImport const import_);
public: ErrorOr<DeprecatedString> debug_description() const;
};struct ArgumentStoreLevel {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
size_t argument_index;
} InObject;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static ArgumentStoreLevel InObject(size_t argument_index);
[[nodiscard]] static ArgumentStoreLevel InStaticStorage();
~ArgumentStoreLevel();
ArgumentStoreLevel& operator=(ArgumentStoreLevel const &);
ArgumentStoreLevel& operator=(ArgumentStoreLevel &&);
ArgumentStoreLevel(ArgumentStoreLevel const&);
ArgumentStoreLevel(ArgumentStoreLevel &&);
private: void __jakt_destroy_variant();
public:
private:
ArgumentStoreLevel() {};
};
struct ParsedStatement: public RefCounted<ParsedStatement> {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
NonnullRefPtr<typename parser::ParsedExpression> expr;
utility::Span span;
} Expression;
struct {
NonnullRefPtr<typename parser::ParsedStatement> statement;
utility::Span span;
} Defer;
struct {
parser::ParsedBlock block;
utility::Span span;
} UnsafeBlock;
struct {
JaktInternal::DynamicArray<parser::ParsedVarDecl> vars;
NonnullRefPtr<typename parser::ParsedStatement> var_decl;
utility::Span span;
} DestructuringAssignment;
struct {
parser::ParsedVarDecl var;
NonnullRefPtr<typename parser::ParsedExpression> init;
utility::Span span;
} VarDecl;
struct {
NonnullRefPtr<typename parser::ParsedExpression> condition;
parser::ParsedBlock then_block;
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> else_statement;
utility::Span span;
} If;
struct {
parser::ParsedBlock block;
utility::Span span;
} Block;
struct {
parser::ParsedBlock block;
utility::Span span;
} Loop;
struct {
NonnullRefPtr<typename parser::ParsedExpression> condition;
parser::ParsedBlock block;
utility::Span span;
} While;
struct {
DeprecatedString iterator_name;
utility::Span name_span;
bool is_destructuring;
NonnullRefPtr<typename parser::ParsedExpression> range;
parser::ParsedBlock block;
utility::Span span;
} For;
struct {
utility::Span value;
} Break;
struct {
utility::Span value;
} Continue;
struct {
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> expr;
utility::Span span;
} Return;
struct {
NonnullRefPtr<typename parser::ParsedExpression> expr;
utility::Span span;
} Throw;
struct {
NonnullRefPtr<typename parser::ParsedExpression> expr;
utility::Span span;
} Yield;
struct {
parser::ParsedBlock block;
utility::Span span;
} InlineCpp;
struct {
NonnullRefPtr<typename parser::ParsedExpression> expr;
parser::ParsedBlock else_block;
parser::ParsedBlock remaining_code;
utility::Span span;
} Guard;
struct {
utility::Span value;
} Garbage;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedStatement>> Expression(NonnullRefPtr<typename parser::ParsedExpression> expr, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedStatement>> Defer(NonnullRefPtr<typename parser::ParsedStatement> statement, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedStatement>> UnsafeBlock(parser::ParsedBlock block, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedStatement>> DestructuringAssignment(JaktInternal::DynamicArray<parser::ParsedVarDecl> vars, NonnullRefPtr<typename parser::ParsedStatement> var_decl, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedStatement>> VarDecl(parser::ParsedVarDecl var, NonnullRefPtr<typename parser::ParsedExpression> init, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedStatement>> If(NonnullRefPtr<typename parser::ParsedExpression> condition, parser::ParsedBlock then_block, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> else_statement, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedStatement>> Block(parser::ParsedBlock block, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedStatement>> Loop(parser::ParsedBlock block, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedStatement>> While(NonnullRefPtr<typename parser::ParsedExpression> condition, parser::ParsedBlock block, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedStatement>> For(DeprecatedString iterator_name, utility::Span name_span, bool is_destructuring, NonnullRefPtr<typename parser::ParsedExpression> range, parser::ParsedBlock block, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedStatement>> Break(utility::Span value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedStatement>> Continue(utility::Span value);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedStatement>> Return(JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> expr, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedStatement>> Throw(NonnullRefPtr<typename parser::ParsedExpression> expr, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedStatement>> Yield(NonnullRefPtr<typename parser::ParsedExpression> expr, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedStatement>> InlineCpp(parser::ParsedBlock block, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedStatement>> Guard(NonnullRefPtr<typename parser::ParsedExpression> expr, parser::ParsedBlock else_block, parser::ParsedBlock remaining_code, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedStatement>> Garbage(utility::Span value);
~ParsedStatement();
ParsedStatement& operator=(ParsedStatement const &);
ParsedStatement& operator=(ParsedStatement &&);
ParsedStatement(ParsedStatement const&);
ParsedStatement(ParsedStatement &&);
private: void __jakt_destroy_variant();
public:
bool equals(NonnullRefPtr<typename parser::ParsedStatement> const rhs_statement) const;
utility::Span span() const;
private:
ParsedStatement() {};
};
struct ParsedExternImport {
  public:
public: bool is_c;public: parser::ParsedNamespace assigned_namespace;public: JaktInternal::DynamicArray<parser::IncludeAction> before_include;public: JaktInternal::DynamicArray<parser::IncludeAction> after_include;public: bool should_auto_import;public: ErrorOr<bool> is_equivalent_to(parser::ParsedExternImport const other) const;
public: ParsedExternImport(bool a_is_c, parser::ParsedNamespace a_assigned_namespace, JaktInternal::DynamicArray<parser::IncludeAction> a_before_include, JaktInternal::DynamicArray<parser::IncludeAction> a_after_include, bool a_should_auto_import);

public: DeprecatedString get_path() const;
public: DeprecatedString get_name() const;
public: ErrorOr<DeprecatedString> debug_description() const;
};struct RecordType {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
JaktInternal::DynamicArray<parser::ParsedField> fields;
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> super_type;
} Struct;
struct {
JaktInternal::DynamicArray<parser::ParsedField> fields;
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> super_type;
} Class;
struct {
NonnullRefPtr<typename parser::ParsedType> underlying_type;
JaktInternal::DynamicArray<parser::ValueEnumVariant> variants;
} ValueEnum;
struct {
bool is_boxed;
JaktInternal::DynamicArray<parser::ParsedField> fields;
JaktInternal::DynamicArray<parser::SumEnumVariant> variants;
} SumEnum;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static RecordType Struct(JaktInternal::DynamicArray<parser::ParsedField> fields, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> super_type);
[[nodiscard]] static RecordType Class(JaktInternal::DynamicArray<parser::ParsedField> fields, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> super_type);
[[nodiscard]] static RecordType ValueEnum(NonnullRefPtr<typename parser::ParsedType> underlying_type, JaktInternal::DynamicArray<parser::ValueEnumVariant> variants);
[[nodiscard]] static RecordType SumEnum(bool is_boxed, JaktInternal::DynamicArray<parser::ParsedField> fields, JaktInternal::DynamicArray<parser::SumEnumVariant> variants);
[[nodiscard]] static RecordType Garbage();
~RecordType();
RecordType& operator=(RecordType const &);
RecordType& operator=(RecordType &&);
RecordType(RecordType const&);
RecordType(RecordType &&);
private: void __jakt_destroy_variant();
public:
ErrorOr<DeprecatedString> record_type_name() const;
private:
RecordType() {};
};
struct ParsedName {
  public:
public: DeprecatedString name;public: utility::Span span;public: ParsedName(DeprecatedString a_name, utility::Span a_span);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedRecord {
  public:
public: DeprecatedString name;public: utility::Span name_span;public: JaktInternal::DynamicArray<parser::ParsedGenericParameter> generic_parameters;public: parser::DefinitionLinkage definition_linkage;public: JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters>> implements_list;public: JaktInternal::DynamicArray<parser::ParsedMethod> methods;public: parser::RecordType record_type;public: JaktInternal::Optional<parser::ExternalName> external_name;public: ParsedRecord(DeprecatedString a_name, utility::Span a_name_span, JaktInternal::DynamicArray<parser::ParsedGenericParameter> a_generic_parameters, parser::DefinitionLinkage a_definition_linkage, JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters>> a_implements_list, JaktInternal::DynamicArray<parser::ParsedMethod> a_methods, parser::RecordType a_record_type, JaktInternal::Optional<parser::ExternalName> a_external_name);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ValueEnumVariant {
  public:
public: DeprecatedString name;public: utility::Span span;public: JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> value;public: ValueEnumVariant(DeprecatedString a_name, utility::Span a_span, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> a_value);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedGenericParameter {
  public:
public: DeprecatedString name;public: utility::Span span;public: JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters>> requires_list;public: bool is_value;public: ParsedGenericParameter(DeprecatedString a_name, utility::Span a_span, JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters>> a_requires_list, bool a_is_value);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedVarDeclTuple {
  public:
public: JaktInternal::DynamicArray<parser::ParsedVarDecl> var_decls;public: utility::Span span;public: ParsedVarDeclTuple(JaktInternal::DynamicArray<parser::ParsedVarDecl> a_var_decls, utility::Span a_span);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedParameter {
  public:
public: bool requires_label;public: parser::ParsedVariable variable;public: JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> default_argument;public: utility::Span span;public: ParsedParameter(bool a_requires_label, parser::ParsedVariable a_variable, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> a_default_argument, utility::Span a_span);

public: bool equals(parser::ParsedParameter const rhs_param) const;
public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedAttribute {
  public:
public: DeprecatedString name;public: utility::Span span;public: JaktInternal::Optional<DeprecatedString> assigned_value;public: JaktInternal::DynamicArray<parser::ParsedAttributeArgument> arguments;public: ParsedAttribute(DeprecatedString a_name, utility::Span a_span, JaktInternal::Optional<DeprecatedString> a_assigned_value, JaktInternal::DynamicArray<parser::ParsedAttributeArgument> a_arguments);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ImportList {
u8 __jakt_variant_index = 0;
union VariantData {
u8 __jakt_uninit_value;
struct {
JaktInternal::DynamicArray<parser::ImportName> value;
} List;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static ImportList List(JaktInternal::DynamicArray<parser::ImportName> value);
[[nodiscard]] static ImportList All();
~ImportList();
ImportList& operator=(ImportList const &);
ImportList& operator=(ImportList &&);
ImportList(ImportList const&);
ImportList(ImportList &&);
private: void __jakt_destroy_variant();
public:
ErrorOr<void> add(parser::ImportName const name);
bool is_empty() const;
private:
ImportList() {};
};
struct ParsedNameWithGenericParameters {
  public:
public: DeprecatedString name;public: utility::Span name_span;public: JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> generic_parameters;public: ParsedNameWithGenericParameters(DeprecatedString a_name, utility::Span a_name_span, JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> a_generic_parameters);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedAlias {
  public:
public: JaktInternal::Optional<parser::ParsedName> alias_name;public: JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters> target;public: ParsedAlias(JaktInternal::Optional<parser::ParsedName> a_alias_name, JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters> a_target);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedModuleImport {
  public:
public: parser::ImportName module_name;public: JaktInternal::Optional<parser::ImportName> alias_name;public: parser::ImportList import_list;public: bool has_same_alias_than(parser::ParsedModuleImport const other) const;
public: ParsedModuleImport(parser::ImportName a_module_name, JaktInternal::Optional<parser::ImportName> a_alias_name, parser::ImportList a_import_list);

public: bool has_same_import_semantics(parser::ParsedModuleImport const other) const;
public: ErrorOr<void> merge_import_list(parser::ImportList const list);
public: bool is_equivalent_to(parser::ParsedModuleImport const other) const;
public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedTrait {
  public:
public: DeprecatedString name;public: utility::Span name_span;public: JaktInternal::DynamicArray<parser::ParsedGenericParameter> generic_parameters;public: parser::ParsedTraitRequirements requirements;public: ParsedTrait(DeprecatedString a_name, utility::Span a_name_span, JaktInternal::DynamicArray<parser::ParsedGenericParameter> a_generic_parameters, parser::ParsedTraitRequirements a_requirements);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedMatchCase {
  public:
public: JaktInternal::DynamicArray<parser::ParsedMatchPattern> patterns;public: utility::Span marker_span;public: parser::ParsedMatchBody body;public: bool has_equal_pattern(parser::ParsedMatchCase const rhs_match_case) const;
public: bool equals(parser::ParsedMatchCase const rhs_match_case) const;
public: ParsedMatchCase(JaktInternal::DynamicArray<parser::ParsedMatchPattern> a_patterns, utility::Span a_marker_span, parser::ParsedMatchBody a_body);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedType: public RefCounted<ParsedType> {
u8 __jakt_variant_index = 0;
union CommonData {
u8 __jakt_uninit_common;
struct {
JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers;
} init_common;
constexpr CommonData() {}
~CommonData() {}
} common;
union VariantData {
u8 __jakt_uninit_value;
struct {
DeprecatedString name;
utility::Span span;
} Name;
struct {
DeprecatedString name;
JaktInternal::DynamicArray<DeprecatedString> namespaces;
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> params;
utility::Span span;
} NamespacedName;
struct {
DeprecatedString name;
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> generic_parameters;
utility::Span span;
} GenericType;
struct {
NonnullRefPtr<typename parser::ParsedType> inner;
utility::Span span;
} JaktArray;
struct {
NonnullRefPtr<typename parser::ParsedType> key;
NonnullRefPtr<typename parser::ParsedType> value;
utility::Span span;
} Dictionary;
struct {
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> types;
utility::Span span;
} JaktTuple;
struct {
NonnullRefPtr<typename parser::ParsedType> inner;
utility::Span span;
} Set;
struct {
NonnullRefPtr<typename parser::ParsedType> inner;
utility::Span span;
} Optional;
struct {
NonnullRefPtr<typename parser::ParsedType> inner;
utility::Span span;
} Reference;
struct {
NonnullRefPtr<typename parser::ParsedType> inner;
utility::Span span;
} MutableReference;
struct {
NonnullRefPtr<typename parser::ParsedType> inner;
utility::Span span;
} RawPtr;
struct {
NonnullRefPtr<typename parser::ParsedType> inner;
utility::Span span;
} WeakPtr;
struct {
JaktInternal::DynamicArray<parser::ParsedParameter> params;
bool can_throw;
NonnullRefPtr<typename parser::ParsedType> return_type;
utility::Span span;
} Function;
struct {
NonnullRefPtr<typename parser::ParsedExpression> expr;
utility::Span span;
} Const;
struct {
NonnullRefPtr<typename parser::ParsedType> base;
DeprecatedString name;
utility::Span span;
} DependentType;
constexpr VariantData() {}
~VariantData() {}
} as;
constexpr u8 __jakt_init_index() const noexcept { return __jakt_variant_index - 1; }ErrorOr<DeprecatedString> debug_description() const;
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedType>> Name(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, DeprecatedString name, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedType>> NamespacedName(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, DeprecatedString name, JaktInternal::DynamicArray<DeprecatedString> namespaces, JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> params, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedType>> GenericType(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, DeprecatedString name, JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> generic_parameters, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedType>> JaktArray(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedType> inner, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedType>> Dictionary(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedType> key, NonnullRefPtr<typename parser::ParsedType> value, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedType>> JaktTuple(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> types, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedType>> Set(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedType> inner, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedType>> Optional(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedType> inner, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedType>> Reference(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedType> inner, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedType>> MutableReference(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedType> inner, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedType>> RawPtr(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedType> inner, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedType>> WeakPtr(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedType> inner, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedType>> Function(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, JaktInternal::DynamicArray<parser::ParsedParameter> params, bool can_throw, NonnullRefPtr<typename parser::ParsedType> return_type, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedType>> Const(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedExpression> expr, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedType>> DependentType(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedType> base, DeprecatedString name, utility::Span span);
[[nodiscard]] static ErrorOr<NonnullRefPtr<ParsedType>> Empty(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers);
~ParsedType();
ParsedType& operator=(ParsedType const &);
ParsedType& operator=(ParsedType &&);
ParsedType(ParsedType const&);
ParsedType(ParsedType &&);
private: void __jakt_destroy_variant();
public:
bool equals(NonnullRefPtr<typename parser::ParsedType> const rhs_parsed_type) const;
utility::Span span() const;
private:
ParsedType() {};
};
template <typename T>
T u64_to_float(u64 const number);
}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::Parser> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::Parser const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ImportName> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ImportName const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ExternalName> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ExternalName const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedVarDecl> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedVarDecl const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::Visibility> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::Visibility const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedField> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedField const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::SumEnumVariant> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::SumEnumVariant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedBlock> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedBlock const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::FunctionType> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::FunctionType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::FunctionLinkage> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::FunctionLinkage const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::InlineState> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::InlineState const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedFunction> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedFunction const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedMethod> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedMethod const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedTraitRequirements> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedTraitRequirements const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::DefinitionLinkage> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::DefinitionLinkage const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::TypeCast> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::TypeCast const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::UnaryOperator> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::UnaryOperator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedCapture> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedCapture const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::VisibilityRestriction> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::VisibilityRestriction const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::IncludeAction> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::IncludeAction const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedMatchPattern> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedMatchPattern const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::CheckedQualifiers> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::CheckedQualifiers const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedExternalTraitImplementation> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedExternalTraitImplementation const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedPatternDefault> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedPatternDefault const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedMatchBody> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedMatchBody const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::NumericConstant> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::NumericConstant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedCall> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedCall const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::BinaryOperator> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::BinaryOperator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::EnumVariantPatternArgument> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::EnumVariantPatternArgument const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedExpression> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedExpression const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedAttributeArgument> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedAttributeArgument const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedVariable> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedVariable const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedTypeQualifiers> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedTypeQualifiers const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedNamespace> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedNamespace const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ArgumentStoreLevel> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ArgumentStoreLevel const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedStatement> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedStatement const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedExternImport> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedExternImport const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::RecordType> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::RecordType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedName> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedName const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedRecord> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedRecord const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ValueEnumVariant> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ValueEnumVariant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedGenericParameter> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedGenericParameter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedVarDeclTuple> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedVarDeclTuple const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedParameter> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedParameter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedAttribute> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedAttribute const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ImportList> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ImportList const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedNameWithGenericParameters> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedNameWithGenericParameters const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedAlias> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedAlias const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedModuleImport> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedModuleImport const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedTrait> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedTrait const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedMatchCase> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedMatchCase const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedType> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
