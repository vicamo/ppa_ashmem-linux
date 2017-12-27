#include <linux/mm.h>
#include <linux/kallsyms.h>

#if 0
[103356.047451] android_ashmem: Unknown symbol kallsyms_lookup_name (err 0)
#endif

#define DEFINE_SYM_R1(name, rtype, a1type)						\
	static rtype (*name ## _ptr)(a1type) = NULL;					\
											\
	rtype name(a1type a1)								\
	{										\
		if (!name ## _ptr)							\
			name ## _ptr = (void*) kallsyms_lookup_name(__stringify(name));	\
		return name ## _ptr(a1);						\
	}

#define DEFINE_SYM_R3(name, rtype, a1type, a2type, a3type)				\
	static rtype (*name ## _ptr)(a1type, a2type, a3type) = NULL;			\
											\
	rtype name(a1type a1, a2type a2, a3type a3)					\
	{										\
		if (!name ## _ptr)							\
			name ## _ptr = (void*) kallsyms_lookup_name(__stringify(name));	\
		return name ## _ptr(a1, a2, a3);					\
	}

#define DEFINE_SYM_R4(name, rtype, a1type, a2type, a3type, a4type)			\
	static rtype (*name ## _ptr)(a1type, a2type, a3type, a4type) = NULL;		\
											\
	rtype name(a1type a1, a2type a2, a3type a3, a4type a4)				\
	{										\
		if (!name ## _ptr)							\
			name ## _ptr = (void*) kallsyms_lookup_name(__stringify(name));	\
		return name ## _ptr(a1, a2, a3, a4);					\
	}

DEFINE_SYM_R3(shmem_file_setup, struct file *, const char *, loff_t, unsigned long)
DEFINE_SYM_R1(shmem_zero_setup, int, struct vm_area_struct *)
DEFINE_SYM_R4(vfs_fallocate, int, struct file *, int, loff_t, loff_t)
