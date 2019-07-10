#include <git2.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	git_libgit2_init();

	const char *GIT_REPO_PATH = ".";

	git_repository *repo = NULL;
	git_repository_open(&repo, GIT_REPO_PATH);

	git_revwalk *walker = NULL;
	git_revwalk_new(&walker, repo);

	git_revwalk_sorting(walker, GIT_SORT_NONE);

	git_revwalk_push_head(walker);

	git_oid oid;
	while (!git_revwalk_next(&oid, walker))
	{
		git_commit *commit = NULL;
		git_commit_lookup(&commit, repo, &oid);

		printf("%s %s\n", git_oid_tostr_s(&oid), git_commit_summary(commit));

		git_commit_free(commit);
	}

	git_revwalk_free(walker);
	git_repository_free(repo);

	git_libgit2_shutdown();

	return 0;
}
