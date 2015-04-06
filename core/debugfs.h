/**
 * @file
 * @brief C source for the ofs (octagram filesystem, outlandish filesystem, or
 *        odd filesystem) kernel module
 * @author Octagram Sun <octagram@qq.com>
 * @version 0.1.0
 * @date 2015
 * @copyright Octagram Sun <octagram@qq.com>
 *
 * @note
 * This header is debugfs interface to the ofs.
 * @note
 * This file is part of ofs, as available from\n
 * * https://gitcafe.com/octagram/ofs\n
 * * https://github.com/octagram-xuanwu/ofs\n
 * @note
 * This file is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License (GPL) as published by the Free
 * Software Foundation, in version 2. The ofs is distributed in the hope
 * that it will be useful, but <b>WITHOUT ANY WARRANTY</b> of any kind.
 */

#ifndef __OFS_DEBUGFS_H__
#define __OFS_DEBUGFS_H__

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********      macros       ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
#define OFSAPI(api)	struct ofs_api __api_##api

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       types       ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
struct api_args;

struct ofs_api {
	struct dentry *entry;
	struct ofs_dbg *dbg;
	struct mutex mtx;
	int (*call)(struct ofs_api *api, const struct api_args *args);
	ino_t result;
};

struct ofs_dbg {
	struct ofs_root *root; /**< ofs root */
#ifdef CONFIG_DEBUG_FS
	struct dentry *this; /**< root directory of debug interface */
	struct dentry *apis; /**< directory: apis */
	struct dentry *tree; /**< child tree */
	OFSAPI(ofs_mkdir_magic);
	OFSAPI(ofs_symlink_magic);
	OFSAPI(ofs_create_magic);
	OFSAPI(ofs_rmdir_magic);
	OFSAPI(ofs_unlink_magic);
	OFSAPI(ofs_rm_singularity);
	OFSAPI(ofs_rm_magic);
	OFSAPI(ofs_rename_magic);
#endif
};

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********         function prototypes         ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
extern
int ofsdebug_construct(struct ofs_root *root);

extern
void ofsdebug_destruct(struct ofs_root *root);

/******** ******** init & exit ******** ********/
extern
int ofs_debugfs_init(void);

extern
void ofs_debugfs_exit(void);

#endif /* debugfs.h */
