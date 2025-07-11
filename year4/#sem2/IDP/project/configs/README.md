# SongRate configs

This repository houses all Kubernetes configuration files for the SongRate project.

## Prerequisites for running locally

- a Kubernetes cluster with LoadBalancer support (recommended: Minikube)
- kubectl
- helm
- docker

## Running locally

To run the project locally, you can use Minikube. First, make sure you have it installed and running.

```bash
minikube start --extra-config=kubelet.authentication-token-webhook=true \
               --extra-config=kubelet.authorization-mode=Webhook
minikube addons enable ingress
minikube addons disable metrics-server

helm repo add kong https://charts.konghq.com
helm repo add portainer https://portainer.github.io/k8s/
helm repo add prometheus-community https://prometheus-community.github.io/helm-charts
helm repo add gitlab https://charts.gitlab.io
helm repo update

kubectl apply -f prerequisites/
kubectl apply -f kong/
kubectl apply -f adminer/
kubectl apply -f database/

# Install Kong ingress controller
helm install kong kong/ingress -n kong --create-namespace

# Install Portainer
helm install portainer portainer/portainer --set image.tag=lts
kubectl apply -f portainer/

# Install the Kube Prometheus stack
helm install prometheus prometheus-community/kube-prometheus-stack \
    --namespace monitoring --create-namespace --version 45.7.1 \
    -f grafana/grafana-values.yaml -f prometheus/prometheus-values.yaml

kubectl apply -f prometheus/
kubectl apply -f grafana/

# Install GitLab Runner
helm install --namespace cicd gitlab-runner --create-namespace \
                -f gitlab-runner/values.yaml gitlab/gitlab-runner

# Deploy our application
kubectl apply -f auth/
kubectl apply -f business-logic/
kubectl apply -f io-service/

minikube tunnel # this will require root privileges and will block the terminal
```

Then acquire the Kong Proxy IP address:

```bash
export PROXY_IP=$(kubectl get svc --namespace kong kong-gateway-proxy \
-o jsonpath='{.status.loadBalancer.ingress[0].ip}')
echo $PROXY_IP
```

Now you can access the public services using the IP address of the Kong Proxy,
e.g. `curl "$PROXY_IP"`, `"$PROXY_IP"/portainer`, `"$PROXY_IP"/adminer` etc.
