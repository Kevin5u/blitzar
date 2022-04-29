workspace(name = "dev_spaceandtime_proofs_gpu")


load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

http_archive(
  name = "bazel_skylib",
  sha256 = "1dde365491125a3db70731e25658dfdd3bc5dbdfd11b840b3e987ecf043c7ca0",
  urls = [
    "https://github.com/bazelbuild/bazel-skylib/releases/download/0.9.0/bazel_skylib-0.9.0.tar.gz",
  ],
)

git_repository(
  name = "build_bazel_rules_cuda",
  commit = "6df14407099e07d422a4a009f27de9e4b47c411c",
  remote = "https://github.com/rnburn/rules_cuda.git",
  # see https://github.com/liuliu/rules_cuda/pull/6
  # remote = "https://github.com/liuliu/rules_cuda.git",
  # commit = "503c98dab4491ef9eae9c30d3c88240d28d4e695",
)

load("@build_bazel_rules_cuda//gpus:cuda_configure.bzl", "cuda_configure")

cuda_configure(name = "local_config_cuda")

git_repository(
    name = "com_github_catchorg_catch2",
    commit = "6f21a3609cea360846a0ca93be55877cca14c86d",
    remote = "https://github.com/catchorg/Catch2",
)
