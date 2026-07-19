# Contributing to Hospital Management System

Thanks for your interest in improving this project! It's a small console-based C++ app, so contributing is meant to be simple. This guide covers how to set up the project, the conventions to follow, and how to submit changes.

## Getting Started

1. Fork the repository and clone your fork:
   ```bash
   git clone https://github.com/<your-username>/<repo-name>.git
   cd <repo-name>
   ```
2. Create a branch for your change:
   ```bash
   git checkout -b feature/short-description
   ```
3. Build the project to confirm your environment works:
   ```bash
   g++ -std=c++17 -Wall -Wextra -o hospital_management hospital_management.cpp
   ./hospital_management
   ```

## Ways to Contribute

- **Bug fixes** — e.g. crashes, incorrect sorting, file I/O edge cases
- **New features** — e.g. edit/delete records, duplicate-ID checks, input validation
- **Code quality** — refactoring, reducing duplication, improving comments
- **Documentation** — improving the README, adding usage examples 
- **Tests** — this project currently has no automated tests; adding some is welcome

If you're planning a larger change (new feature, restructuring), please open an issue first to discuss the approach before investing a lot of time.

## AI Usage Policy

- AI usage to Generate some functions or small portion is permissible but writing whole file with AI will not be entertained
- Dont add things you dont understand or are inefficient by using AI

## Coding Style

To keep the codebase consistent:

- **C++17**, compiled cleanly with `-Wall -Wextra` (no new warnings)
- 4-space indentation, no tabs
- `camelCase` for variables and functions, `PascalCase` for class names
- Prefer `const` references for function parameters that aren't modified
- Keep class members `private` with getters, following the existing `Hospital`/`Patient` pattern
- Use `std::vector` rather than fixed-size arrays for collections
- Avoid raw `new`/`delete`; prefer standard containers and RAII (e.g. `ifstream`/`ofstream`)
- Match the existing menu-driven structure in `main()` rather than introducing a different control flow, unless the PR is specifically about restructuring it

## Commit Messages

Use short, descriptive commit messages in the imperative mood:

```
Add duplicate hospital ID check
Fix sort stability in sortByRatingReviews
Update README with build instructions
```

## Submitting a Pull Request

1. Make sure your branch builds without warnings and the program still runs correctly for the existing menu options.
2. Manually test the feature/fix you changed (add a hospital/patient, run the relevant display/sort option, check the output and the resulting `.txt` file).
3. Update `README.md` if your change affects usage, the data file format, or the menu.
4. Push your branch and open a pull request against `main`, describing:
   - What the change does and why
   - How you tested it
   - Any limitations or follow-up work
5. Be responsive to review feedback  small, focused PRs are easier to review and merge quickly.

## Reporting Issues

When filing a bug report, please include:

- Steps to reproduce (menu options selected, input entered)
- Expected behavior vs. actual behavior
- Your compiler and OS (e.g. `g++ 11.4`, Ubuntu 22.04)
- Relevant contents of `hospitals.txt` / `patients.txt` if the issue is data-related

## Code of Conduct

Be respectful and constructive in issues, discussions, and reviews. This is a learning-oriented project  questions and beginner-friendly contributions are welcome.
