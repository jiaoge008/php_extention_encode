/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_muyi.h"
#include "ext/standard/base64.h"
#include "ext/standard/php_string.h"

/* If you declare any globals in php_muyi.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(muyi)
*/

/* True global resources - no need for thread safety here */
static int le_muyi;

/* {{{ muyi_functions[]
 *
 * Every user visible function must have an entry in muyi_functions[].
 */
const zend_function_entry muyi_functions[] = {
	PHP_FE(confirm_muyi_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(encodeStr,	NULL)
	PHP_FE(decodeStr,	NULL)
	PHP_FE_END	/* Must be the last line in muyi_functions[] */
};
/* }}} */

/* {{{ muyi_module_entry
 */
zend_module_entry muyi_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"muyi",
	muyi_functions,
	PHP_MINIT(muyi),
	PHP_MSHUTDOWN(muyi),
	PHP_RINIT(muyi),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(muyi),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(muyi),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_MUYI_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MUYI
ZEND_GET_MODULE(muyi)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("muyi.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_muyi_globals, muyi_globals)
    STD_PHP_INI_ENTRY("muyi.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_muyi_globals, muyi_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_muyi_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_muyi_init_globals(zend_muyi_globals *muyi_globals)
{
	muyi_globals->global_value = 0;
	muyi_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(muyi)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(muyi)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(muyi)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(muyi)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(muyi)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "muyi support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_muyi_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_muyi_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "muyi", arg);
	RETURN_STRINGL(strg, len, 0);
}

PHPAPI char *base64url_encode(char *s,int len)
{
    zval *return_value=NULL;
    char *str;
    s = php_strtr(s,len,"+/","-_",2);
    str = php_trim(s,len,"=",1,return_value,2 TSRMLS_DC);
    return str;
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/

/* {{{ proto string encodeStr(string str)
    */
PHP_FUNCTION(encodeStr)
{
    char *str = NULL;
    int argc = ZEND_NUM_ARGS();
    int str_len;
    int i,ret_length;
    char *result;
    int ord_long;
    unsigned char *ret;
    
    if (zend_parse_parameters(argc TSRMLS_CC, "s", &str, &str_len) == FAILURE)
        return;
    result = (char *)emalloc(str_len+1);
    
    for(i=0;i<str_len;i++)
    {
        ord_long = (int)((unsigned char)str[i]);
        switch(i%6)
        {
            case 0:
                result[i] = (char)(ord_long-1);
                break;
            case 1:
                result[i] = (char)(ord_long-5);
                break;
            case 2:
                result[i] = (char)(ord_long-7);
                break;
            case 3:
                result[i] = (char)(ord_long-2);
                break;
            case 4:
                result[i] = (char)(ord_long-4);
                break;
            case 5:
                result[i] = (char)(ord_long-9);
                break;
            default:;
        }
    }
    result[str_len] = '\0';
    
    ret = php_base64_encode((unsigned char*)result, str_len, &ret_length);
    if(ret == NULL)
    {
        RETURN_FALSE;
    }
    ret = php_strtr(ret,ret_length,"+/","-_",2);
    php_trim(ret,ret_length,"=",1,return_value,2 TSRMLS_DC);
    //str = base64url_encode(ret,ret_length);
    //RETURN_STRINGL((char*)str,ret_length,0);
}
/* }}} */

/* {{{ proto string decodeStr(string str)
    */
PHP_FUNCTION(decodeStr)
{
    char *str = NULL;
    char *result = NULL;
    int argc = ZEND_NUM_ARGS();
    int str_len,ret_len,i;
    long ord_long;
    zend_bool strict = 0;
    
    if (zend_parse_parameters(argc TSRMLS_CC, "s", &str, &str_len) == FAILURE)
        return;
    str = php_strtr(str,str_len,"-_","+/",2);
    str = php_base64_decode_ex((unsigned char*)str,str_len,&ret_len,strict);
    result = (char *)emalloc(ret_len+1);
    for(i=0;i<ret_len;i++)
    {
        ord_long = (long)((unsigned char)str[i]);
        switch(i%6)
        {
            case 0:
                result[i] = (char)(ord_long+1);
                break;
            case 1:
                result[i] = (char)(ord_long+5);
                break;
            case 2:
                result[i] = (char)(ord_long+7);
                break;
            case 3:
                result[i] = (char)(ord_long+2);
                break;
            case 4:
                result[i] = (char)(ord_long+4);
                break;
            case 5:
                result[i] = (char)(ord_long+9);
                break;
            default:;
        }
    }
    result[ret_len] = '\0';
    RETURN_STRINGL((char*)result,ret_len,0);
}
/* }}} */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
