/* helloworld extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_helloworld.h"

/* {{{ void helloworld_test1()
 */
PHP_FUNCTION(helloworld_test1)
{
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("The1 extension %s is loaded and working!\r\n", "helloworld");
}
/* }}} */

/* {{{ string helloworld_test2( [ string $var ] )
 */
PHP_FUNCTION(helloworld_test2)
{
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}
PHP_FUNCTION(my_sum){
	zval *array,*key,*entry;
	zend_ulong num_idx;
	zend_string *str_idx;

	//ZEND_PARSE_PARAMETERS_START(2,2)
	//	//Z_PARAM_OPTIONAL
	//	//Z_PARAM_STRING(var, var_len)
	//	//Z_PARAM_LONG(a)
	//	//Z_PARAM_LONG(b)
	//	Z_PARAM_ZVAL(key)
	//	Z_PARAM_ARRAY(array)
	//ZEND_PARSE_PARAMETERS_END();
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"za",&key,&array) != SUCCESS){
		return;
	}

	// get that first argument is key
	if (Z_TYPE_P(key) == IS_LONG) {
		zend_long arg = Z_LVAL_P(key);
		zend_printf("numerical arg=%d \n", arg);
	} else if (Z_TYPE_P(key) == IS_STRING) {
		zend_string *arg = Z_STR_P(key);
		zend_printf("string arg=%s \n", arg->val);
	}

	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(array),num_idx,str_idx,entry){
		if(str_idx){
			zend_printf("string key=%s \n",str_idx->val);
		}else{
			zend_printf("numerical key=%d \n",num_idx);
		}
		zend_printf("type=%d \n",Z_TYPE_P(entry));

		if(Z_TYPE_P(entry) == IS_LONG){
			zend_long value = Z_LVAL_P(entry);
			zend_printf("numerical value=%d \n",value);
		}else if(Z_TYPE_P(entry) == IS_STRING){
			zend_string *value = Z_STR_P(entry);
			zend_printf("string value=%s \n",value->val);
		}else if(Z_TYPE_P(entry) == IS_ARRAY){
			zend_array *value = Z_ARR_P(entry);
			zval *entry2;
			zend_ulong num_idx2;
			zend_string *str_idx2;
			ZEND_HASH_FOREACH_KEY_VAL(value,num_idx2,str_idx2,entry2){
				if(str_idx2){
					zend_printf("string2 key=%s \n",str_idx2->val);
				}else{
					zend_printf("numerical2 key=%d \n",num_idx2);
				}
				zend_printf("type2=%d \n",Z_TYPE_P(entry2));

				if(Z_TYPE_P(entry2) == IS_LONG){
					zend_long value2 = Z_LVAL_P(entry2);
					zend_printf("numerical2 value=%d \n",value2);
				}else if(Z_TYPE_P(entry2) == IS_STRING){
					zend_string *value2 = Z_STR_P(entry2);
					zend_printf("string2 value=%s \n",value2->val);
				}else if(Z_TYPE_P(entry2) == IS_ARRAY){
					zend_array *value2 = Z_ARR_P(entry2);
					zval *entry3;
					zend_ulong num_idx3;
					zend_string *str_idx3;
					ZEND_HASH_FOREACH_KEY_VAL(value2,num_idx3,str_idx3,entry3){
						if(str_idx3){
							zend_printf("string3 key=%s \n",str_idx3->val);
						}else{
							zend_printf("numerical3 key=%d \n",num_idx3);
						}
						zend_printf("type3=%d \n",Z_TYPE_P(entry3));

						if(Z_TYPE_P(entry3) == IS_LONG){
							zend_long value3 = Z_LVAL_P(entry3);
							zend_printf("numerical3 value=%d \n",value3);
						}else if(Z_TYPE_P(entry3) == IS_STRING){
							zend_string *value3 = Z_STR_P(entry3);
							zend_printf("string3 value=%s \n",value3->val);
						}
					}ZEND_HASH_FOREACH_END();
				}
			}ZEND_HASH_FOREACH_END();
		}
		//switch(Z_TYPE_P(entry)){
		//	case IS_LONG:
		//		zend_long value = Z_LVAL_P(entry);
		//		zend_printf("numerical value=%d \n",value);
		//		break;
		//	case IS_STRING:
		//		zend_string *value = Z_STR_P(entry);
		//		zend_printf("string value=%s \n",value->val);
		//		break;
		//	default:
		//		break;
		//}
	}ZEND_HASH_FOREACH_END();
	//if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"all",z_array,a,b) != SUCCESS){
	//if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"a",&z_array,&a,&b) != SUCCESS){
	//	return;
	//}
	
	//RETURN_LONG(s);
}
/* }}}*/

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(helloworld)
{
#if defined(ZTS) && defined(COMPILE_DL_HELLOWORLD)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(helloworld)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "helloworld support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_helloworld_test1, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_helloworld_test2, 0)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ helloworld_functions[]
 */
static const zend_function_entry helloworld_functions[] = {
	PHP_FE(helloworld_test1,		arginfo_helloworld_test1)
	PHP_FE(helloworld_test2,		arginfo_helloworld_test2)
	PHP_FE(my_sum,NULL)
	PHP_FE_END
};
/* }}} */

/* {{{ helloworld_module_entry
 */
zend_module_entry helloworld_module_entry = {
	STANDARD_MODULE_HEADER,
	"helloworld",					/* Extension name */
	helloworld_functions,			/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(helloworld),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(helloworld),			/* PHP_MINFO - Module info */
	PHP_HELLOWORLD_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_HELLOWORLD
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(helloworld)
#endif

