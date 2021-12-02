INC_DIR=$1

GIT_VERSION=$(git describe --always --tags)

echo "#define SEQWISH_GIT_VERSION" \"$GIT_VERSION\" > $1/seqwish_git_version.hpp.tmp
diff $1/seqwish_git_version.hpp.tmp $1/seqwish_git_version.hpp >/dev/null || cp $1/seqwish_git_version.hpp.tmp $1/seqwish_git_version.hpp
rm -f $1/seqwish_git_version.hpp.tmp