#! /bin/bash

ScriptPath=$0
Dir=$(cd $(dirname "$ScriptPath"); pwd)
Basename=$(basename "$ScriptPath")
CMakeDir=${SIS_CMAKE_BUILD_DIR:-$Dir/_build}
MakeCmd=${SIS_CMAKE_COMMAND:-make}


# ##########################################################
# command-line handling

while [[ $# -gt 0 ]]; do

  case $1 in
    --help)

      [ -f "$Dir/.sis/script_info_lines.txt" ] && cat "$Dir/.sis/script_info_lines.txt"
      cat << EOF
Runs all (matching) unit-test programs

$ScriptPath [ ... flags/options ... ]

Flags/options:

    behaviour:


    standard flags:

    --help
        displays this help and terminates

EOF

      exit 0
      ;;
    *)

      >&2 echo "$ScriptPath: unrecognised argument '$1'; use --help for usage"

      exit 1
      ;;
  esac

  shift
done


# ##########################################################
# main()

mkdir -p $CMakeDir || exit 1

cd $CMakeDir

echo "Executing make and then running all test programs"

status=0

if make; then

  for f in $(find $Dir -type f -perm +111 '(' -name '*chomp*test*' ')')
  do

    echo
    echo "executing $f:"

    if $f; then

      :
    else

      status=$?

      break 1
    fi
  done
else

  status=$?
fi

cd ->/dev/null

exit $status


# ############################## end of file ############################# #

