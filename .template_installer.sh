#!/bin/bash

PACKAGE_DIR="./pkg"
UPDATABLE_FILES=()
UPDATABLE_DIRS=()
INSTALLABLE_FILES=()

check_if_exists(){
    PACKAGE_FILES=(./*)
    for PACKAGE_FILE in "${PACKAGE_FILES[@]}"; 
    do 
        if [ -f ${USER_PWD}/$PACKAGE_FILE ];
        then
            echo "File found:         ${USER_PWD}/$PACKAGE_FILE"
            UPDATABLE_FILES+=($PACKAGE_FILE) 
        elif [ -d ${USER_PWD}/$PACKAGE_FILE ]; 
        then 
            echo "Directory found:    ${USER_PWD}/$PACKAGE_FILE"
            UPDATABLE_DIRS+=($PACKAGE_FILE)
        else 
            echo "Not found:          ${USER_PWD}/$PACKAGE_FILE"
            INSTALLABLE_FILES+=($PACKAGE_FILE)
        fi
    done
}

#Arg1: Reference_File
#Arg2: Checked_file
get_file_diff(){
    REFERENCE_FILE=$1
    CHECKED_FILE=$2
    
    if [ -f $CHECKED_FILE ]; 
    then 
        diff -q $REFERENCE_FILE $CHECKED_FILE
    else 
        echo "$CHECKED_FILE is not a file! Aborting diff." 
    fi
}

#Arg1: File that contains marked lines
remove_marked_lines() {
    FILE=$1
    REGEX="\(#@\+[\s\S]*#@-.*\)"
    START_REGEX="\(#@\+[\s\S]*\)"
    END_REGEX="\(#@-.*\)"

    sed "/$START_REGEX/,/$END_REGEX/{//!d}" $FILE > ${FILE}_changed
    sed -i "/$START_REGEX/d" ${FILE}_changed
    sed -i "/$END_REGEX/d" ${FILE}_changed
}

check_updatable_files() {
    TMP_LIST=()
    for FILE in "${UPDATABLE_FILES[@]}"; 
    do
        FILE_DIF=$(get_file_diff ${USER_PWD}/$FILE ./$FILE) 
        if [ -z "$FILE_DIF" ];
        then 
            echo "$FILE has no applicable udpates!" 
        else 
            echo "$FILE is updatable! Adding to updatable file list"
            TMP_LIST+=$FILE
        fi
    done

    UPDATABLE_FILES=$TMP_LIST
}

do_install() {
    
    echo "Installing files into:"
    echo "${USER_PWD}/"
    cp -rf ${PACKAGE_DIR}/* ${USER_PWD}/
    cp -rf ${PACKAGE_DIR}/.* ${USER_PWD}/
    
    mkdir ${USER_PWD}/includes ${USER_PWD}/sources 
    touch ${USER_PWD}/includes/YOUR_HEADER_FILES_GO_HERE
    touch ${USER_PWD}/sources/YOUR_SOURCE_FILES_GO_HERE
}

do_update(){ 
    check_updatable_files
    
    if [ ${#INSTALLABLE_FILES[@]} -ne 0 ]; 
    then 
        echo "Installing new files: ${INSTALLABLE_FILES[@]}" 
        for FILE in "${INSTALLABLE_FILES[@]}"; 
        do 
            rsync -rtv ${FILE} ${USER_PWD}/
        done
    elif [ ${#UPDATABLE_FILES[@]} -ne 0 ]; 
    then
        echo "Updating files: ${UPDATABLE_FILES[@]}"
        #update_files
    elif [ ${#UPDATABLE_DIRS[@]} -ne 0 ];
    then
        echo "Updating directories: ${UPDATABLE_DIRS[@]}"
        #update_dirs
    else 
        echo "Nothing to update! Aborting..."
        exit 1
    fi
}

do_cleanup(){
    echo "Cleaning up archives" 
    rm -rf ${USER_PWD}/Project_Template_Files*
    exit 0
}

# =================== MAIN ENTRY POINT ====================

check_if_exists
echo "This package contains:" 
ls -la $PACKAGE_DIR
echo "Installable: ${INSTALLABLE_FILES[@]}"
echo "Updatable: ${UPDATABLE_FILES[@]}"

if [ ${#INSTALLABLE_FILES[@]} -ne 0 ] && [ ${#UPDATABLE_FILES[@]} -eq 0 ]; 
then 
    echo "Deteced a clean project setup. Installing from scratch!"
    do_install
elif [ ${#UPDATABLE_FILES[@]} -ne 0 ];
then
    echo "Detected previous setup. Trying to update!"
    do_update
fi

do_cleanup
