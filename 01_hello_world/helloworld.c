#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Erick Winck");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("Hello world com printk");

/*
 * init_function - Função inicial, printa "Hello world!" com printk
 */
static __init int init_function(void)
{
	printk("Hello world!\n");
	return 0;
}

/*
 * exit_function - Função de saída, printa "Goodbye world!" com printk
 */
static __exit void exit_function(void)
{
	printk("Goodbye world!\n");
}

module_init(init_function);
module_exit(exit_function);
