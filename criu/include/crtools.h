#ifndef __CR_CRTOOLS_H__
#define __CR_CRTOOLS_H__

#include <sys/types.h>

#include "common/list.h"
#include "servicefd.h"

#include "images/inventory.pb-c.h"

#define CR_FD_PERM		(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

extern int check_img_inventory(void);
extern int write_img_inventory(InventoryEntry *he);
extern int prepare_inventory(InventoryEntry *he);
extern int add_post_prepare_cb(int (*actor)(void *data), void *data);
extern bool deprecated_ok(char *what);
extern int cr_dump_tasks(pid_t pid);
extern int cr_pre_dump_tasks(pid_t pid);
extern int cr_restore_tasks(void);
extern int convert_to_elf(char *elf_path, int fd_core);
extern int cr_check(void);
extern int cr_dedup(void);

extern int check_add_feature(char *arg);
extern void pr_check_features(const char *offset, const char *sep, int width);

#define add_post_prepare_cb_once(actor, data)			\
	({							\
		static int __cb_called = 0;			\
		int ret = 0;					\
								\
		if (!__cb_called) {				\
			ret = add_post_prepare_cb(actor, data);	\
			__cb_called = 1;			\
		}						\
								\
		ret;						\
	})

#endif /* __CR_CRTOOLS_H__ */
