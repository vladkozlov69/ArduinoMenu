class prompt;
class menu;
class menuOut;
template <typename T> class menuField;

#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2

#define FOR_EACH_1(what, x, ...) what(x)
#define FOR_EACH_2(what, x, ...)\
  what(x)\
  FOR_EACH_1(what,  __VA_ARGS__)
#define FOR_EACH_3(what, x, ...)\
  what(x)\
  FOR_EACH_2(what, __VA_ARGS__)
#define FOR_EACH_4(what, x, ...)\
  what(x)\
  FOR_EACH_3(what,  __VA_ARGS__)
#define FOR_EACH_5(what, x, ...)\
  what(x)\
 FOR_EACH_4(what,  __VA_ARGS__)
#define FOR_EACH_6(what, x, ...)\
  what(x)\
  FOR_EACH_5(what,  __VA_ARGS__)
#define FOR_EACH_7(what, x, ...)\
  what(x)\
  FOR_EACH_6(what,  __VA_ARGS__)
#define FOR_EACH_8(what, x, ...)\
  what(x)\
  FOR_EACH_7(what,  __VA_ARGS__)
#define FOR_EACH_9(what, x, ...)\
  what(x)\
  FOR_EACH_8(what,  __VA_ARGS__)
#define FOR_EACH_10(what, x, ...)\
  what(x)\
  FOR_EACH_9(what,  __VA_ARGS__)
#define FOR_EACH_11(what, x, ...)\
  what(x)\
  FOR_EACH_10(what,  __VA_ARGS__)
#define FOR_EACH_12(what, x, ...)\
  what(x)\
  FOR_EACH_11(what,  __VA_ARGS__)
#define FOR_EACH_13(what, x, ...)\
  what(x)\
  FOR_EACH_12(what,  __VA_ARGS__)
#define FOR_EACH_14(what, x, ...)\
  what(x)\
  FOR_EACH_13(what,  __VA_ARGS__)
#define FOR_EACH_15(what, x, ...)\
  what(x)\
  FOR_EACH_14(what,  __VA_ARGS__)
#define FOR_EACH_16(what, x, ...)\
  what(x)\
  FOR_EACH_15(what,  __VA_ARGS__)

#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) FOR_EACH_ARG_N(__VA_ARGS__)
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, N, ...) N
#define FOR_EACH_RSEQ_N() 16,15,14,13,12,11,10,9,8, 7, 6, 5, 4, 3, 2, 1, 0

#define FOR_EACH_(N, what, x, ...) CONCATENATE(FOR_EACH_, N)(what, x, __VA_ARGS__)
#define FOR_EACH(what, x, ...) FOR_EACH_(FOR_EACH_NARG(x, __VA_ARGS__), what, x, __VA_ARGS__)

#define DECL(x) DECL_##x
#define DEF(x) DEF_##x,

#define MENU(id,text,...)\
  FOR_EACH(DECL,__VA_ARGS__)\
  prompt* const id##_data[]={\
    FOR_EACH(DEF,__VA_ARGS__)\
  };\
  menu id (text,sizeof(id##_data)/sizeof(prompt*),id##_data);

#define CHOOSE(target,id,text,...)\
  FOR_EACH(menuValue<typeof(target)> DECL_VALUE,__VA_ARGS__)\
  menuValue<typeof(target)>* const id##_data[]={\
    FOR_EACH(DEF,__VA_ARGS__)\
  };\
  menuChoice<typeof(target)> id (text,sizeof(id##_data)/sizeof(prompt*),id##_data,target);

#define TOGGLE(target,id,text,...)\
  FOR_EACH(menuValue<typeof(target)> DECL_VALUE,__VA_ARGS__)\
  menuValue<typeof(target)>* const id##_data[]={\
    FOR_EACH(DEF,__VA_ARGS__)\
  };\
  menuToggle<typeof(target)> id (text,sizeof(id##_data)/sizeof(prompt*),id##_data,target);

/*#define GET_MACRO(_1,_2,NAME,...) NAME
#define VALUE(...) GET_MACRO(__VA_ARGS__, EXPLICIT_VALUE, IMPLICIT_VALUE)(__VA_ARGS__)*/

#define OP(...) OP_(__COUNTER__,__VA_ARGS__)
#define FIELD(...) FIELD_(__COUNTER__,__VA_ARGS__)
#define VALUE(...) VALUE_(__COUNTER__,__VA_ARGS__)
#define TEXTFIELD(...) TEXTFIELD_(__COUNTER__,__VA_ARGS__)

#define DECL_OP_(cnt,...) prompt op##cnt(__VA_ARGS__);
#define DECL_FIELD_(cnt,target,...) menuField<typeof(target)> _menuField##cnt(target,__VA_ARGS__);
#define DECL_TEXTFIELD_(cnt,target,...) menuTextField _menuTextField##cnt(target,__VA_ARGS__);
#define DECL_SUBMENU(id)
#define DECL_VALUE(...) _##__VA_ARGS__
#define _VALUE_(cnt,...) choice##cnt(__VA_ARGS__);

#define DEF_OP_(cnt,...) &op##cnt
#define DEF_FIELD_(cnt,...) &_menuField##cnt
#define DEF_TEXTFIELD_(cnt,...) &_menuTextField##cnt
#define DEF_SUBMENU(id) &id
#define DEF_VALUE(id) &id
#define DEF_VALUE_(cnt,...) &choice##cnt