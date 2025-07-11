# Cloud Computing Project - Adrian-George Dumitrache [342C1]

This file contains instructions for reproducing the project infrastructure.

## Task 0

```bash
bash scripts/task0.sh
```

This will:

* Update packages
* Install kubectl
* Install kind

Testing:
```bash
kubectl version
kind --version
```

## Task 1

```bash
bash scripts/task1.sh
```

This will:
* Create a kind cluster
* Use kubectl to show its status

After waiting a bit, you can check the status of the cluster with:
```bash
kubectl get nodes
```

## Task 2

```bash
bash scripts/task2.sh
```

This will:
* Create a namespace called `gitea`
* Add the `gitea` helm repository
* Install the `gitea` chart in the `gitea` namespace

After waiting a bit, you can access gitea by forwarding the service to your
localhost:

```bash
kubectl --namespace gitea port-forward svc/gitea-http 3000:3000
```

Then, you can access the Gitea web interface at `http://localhost:3000`. From
there, you can register a new user and create a new repository.

## Task 3

```bash
bash scripts/task3.sh
```

This will:
* Create a new namespace called `ArgoCD`
* Install the `argocd` manifest in the `ArgoCD` namespace
* Install the `argocd` CLI tool
* Create a secret for accessing the Gitea repository

After waiting a bit, you can access the ArgoCD web interface by forwarding the
service to your localhost:

```bash
kubectl --namespace argocd port-forward svc/argocd-server 8080:443
```

And login using `admin` as username and the password from the following command:

```bash
argocd admin initial-password -n argocd | head -n 1
```

The repository should be automatically added to ArgoCD. You can check this in
the Settings -> Repositories tab. If the connection failed, the most likely
culprit is the fact that the repository is empty (as in, it doesn't contain
any commits), so make sure to add at least one commit to the repository.

## Task 4

```bash
bash scripts/task4.sh
```

This will:

* build the docker image for the nginx server serving the website
* login to the docker registry
* push the image to a docker registry (modify as needed)
* add this entire project to the gitea repo
* apply the application object for auto deploying cloud courses

We can now check the ArgoCD UI to see how our deployment is going or push some
dummy commits in the cloud courses manifests to see the auto sync in action.

## Task 5

The manifests for the cloud courses website already include a liveness probe,
we can check that it works correctly by looking a the nginx pod logs:

```bash
kubectl get pods # copy the pod name from here
kubectl logs <pod-name>
```

The output should include some requests coming from "kube-probe" every couple
of seconds, like so:

```
10.244.0.1 - - [17/Apr/2025:10:11:03 +0000] "GET / HTTP/1.1" 200 69980 "-" "kube-probe/1.32" "-"
10.244.0.1 - - [17/Apr/2025:10:11:13 +0000] "GET / HTTP/1.1" 200 69980 "-" "kube-probe/1.32" "-"
10.244.0.1 - - [17/Apr/2025:10:11:23 +0000] "GET / HTTP/1.1" 200 32768 "-" "kube-probe/1.32" "-"
10.244.0.1 - - [17/Apr/2025:10:11:33 +0000] "GET / HTTP/1.1" 200 32768 "-" "kube-probe/1.32" "-"
10.244.0.1 - - [17/Apr/2025:10:11:43 +0000] "GET / HTTP/1.1" 200 69980 "-" "kube-probe/1.32" "-"
10.244.0.1 - - [17/Apr/2025:10:11:53 +0000] "GET / HTTP/1.1" 200 69980 "-" "kube-probe/1.32" "-"
10.244.0.1 - - [17/Apr/2025:10:12:03 +0000] "GET / HTTP/1.1" 200 69980 "-" "kube-probe/1.32" "-"
```

