/*
    FUSE: Filesystem in Userspace
    Copyright (C) 2001  Miklos Szeredi (mszeredi@inf.bme.hu)

    This program can be distributed under the terms of the GNU GPL.
    See the file COPYING.
*/

/* This file defines the kernel interface of FUSE */

/** Version number of this interface */
#define FUSE_KERNEL_VERSION 1

/** The inode number of the root indode */
#define FUSE_ROOT_INO 1

/** Opening this will yield a new control file */
#define FUSE_DEV "/proc/fs/fuse/dev"

/** Data passed to mount */
struct fuse_mount_data {
	/** Must be set to FUSE_KERNEL_VERSION */
	int version;
	
	/** The control file descriptor */
	int fd;
	
	/** The file type of the root inode */
	unsigned int rootmode;

	/** The user ID of the user initiating this mount */
	unsigned int uid;
	
	/** FUSE specific mount flags */
	unsigned int flags;
};

struct fuse_attr {
	unsigned int        mode;
	unsigned int        nlink;
	unsigned int        uid;
	unsigned int        gid;
	unsigned int        rdev;
	unsigned long long  size;
	unsigned long       _dummy;
	unsigned long       blocks;
	unsigned long       atime;
	unsigned long       mtime;
	unsigned long       ctime;
};

#define FATTR_MODE	(1 << 0)
#define FATTR_UID	(1 << 1)
#define FATTR_GID	(1 << 2)
#define FATTR_SIZE	(1 << 3)
#define FATTR_UTIME	(1 << 4)

enum fuse_opcode {
	FUSE_LOOKUP	= 1,
	FUSE_FORGET	= 2,
	FUSE_GETATTR	= 3,
	FUSE_SETATTR	= 4,
	FUSE_READLINK	= 5,
	FUSE_SYMLINK	= 6,
	FUSE_GETDIR	= 7,
	FUSE_MKNOD	= 8,
	FUSE_MKDIR	= 9,
	FUSE_UNLINK	= 10,
	FUSE_RMDIR	= 11,
	FUSE_RENAME	= 12,
	FUSE_LINK	= 13,
	FUSE_OPEN	= 14,
	FUSE_READ	= 15,
	FUSE_WRITE	= 16,
};

/* Conservative buffer size for the client */
#define FUSE_MAX_IN 8192

struct fuse_lookup_out {
	unsigned long ino;
	struct fuse_attr attr;
};

struct fuse_forget_in {
	int version;
};

struct fuse_getattr_out {
	struct fuse_attr attr;
};

struct fuse_getdir_out {
	int fd;
	void *file; /* Used by kernel only */
};

struct fuse_mknod_in {
	unsigned short mode;
	unsigned short rdev;
	char name[0];
};

struct fuse_mknod_out {
	unsigned long ino;
	struct fuse_attr attr;
};

struct fuse_mkdir_in {
	unsigned short mode;
	char name[0];
};

struct fuse_rename_in {
	unsigned long newdir;
	char names[0];
};

struct fuse_link_in {
	unsigned long newdir;
	char name[0];
};

struct fuse_setattr_in {
	struct fuse_attr attr;
	unsigned int valid;
};

struct fuse_setattr_out {
	struct fuse_attr attr;
};

struct fuse_open_in {
	unsigned int flags;
};

struct fuse_read_in {
	unsigned long long offset;
	unsigned int size;
};

struct fuse_write_in {
	unsigned long long offset;
	unsigned int size;
	char buf[0];
};

struct fuse_in_header {
	int unique;
	enum fuse_opcode opcode;
	unsigned long ino;
};

struct fuse_out_header {
	int unique;
	int error;
};

struct fuse_dirent {
	unsigned long ino;
	unsigned short namelen;
	unsigned char type;
	char name[256];
};

#define FUSE_NAME_OFFSET ((unsigned int) ((struct fuse_dirent *) 0)->name)
#define FUSE_DIRENT_ALIGN(x) (((x) + sizeof(long) - 1) & ~(sizeof(long) - 1))
#define FUSE_DIRENT_SIZE(d) \
	FUSE_DIRENT_ALIGN(FUSE_NAME_OFFSET + (d)->namelen)

/* 
 * Local Variables:
 * indent-tabs-mode: t
 * c-basic-offset: 8
 * End:
 */