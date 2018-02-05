#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/cacheflush.h>

MODULE_LICENSE("Dual BSD/GPL");


int flush_module_read_procmem(char *page, char **start, off_t offset, int count, int *eof, void *data);

int flush_module_read_procmem(char *buf, char **start, off_t offset, int count, int *eof, void *data)
{
  flush_cache_all();
  return 0;
}

static int flush_init(void)
{
      printk("### Flush-Cache module - %s %s ###\n", __DATE__, __TIME__);
      create_proc_read_entry("flush_module", 0, NULL, flush_module_read_procmem, NULL);
          return 0;
}

static void flush_exit(void)
{
  remove_proc_entry("flush_module", NULL);
  printk("Flush module unloaded\n");
}

module_init(flush_init);
module_exit(flush_exit);

