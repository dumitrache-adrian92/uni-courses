# Cloud Computing Project - Adrian-George Dumitrache [342C1]

The project's manifests are organized by service (e.g. `gitea`, `argocd`,
etc.), so all necessary files for each service are in the same folder. Most
services don't require that many manifests, being installed mostly using Helm
charts/remote repositories.

To reproduce the project infrastructure, you can use the scripts in the
`scripts` folder. Each script corresponds to a task in the project, more in
`writeup.md`.

Note that this repo also includes a modified copy of the cloud courses project,
the main difference being the `Dockerfile`, which now builds the app and
transfers the generated static website to an `nginx` instance.

