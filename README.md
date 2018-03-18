# Efficient-File-System
This file systems supports the following features:
  1. Listing a directory
  2. Adding a directory
  3. Renaming a directory

# Listing a directory:
  Command: ls <absolute_path>
  Examples: ls /, ls /dir_1
  Note: Absolute path has to begin with /
  
# Adding a directory:
  Command: mkdir <absolute_path>
  Examples: mkdirls /dir_1
  Note: Absolute path has to begin with /. Currently it does not support nested directory creation.
  
# Rename a directory:
  Command: renmae <absolute_path> <new_directory_name>
  Example: rename /dir_1 dir_new
  Outcome: /dir_1 will be replaced by /dir_new
 
# To exit:
  Command: exit
