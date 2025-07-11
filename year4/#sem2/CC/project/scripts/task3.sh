#!/bin/bash

# Create namespace for ArgoCD
script_dir=$(dirname "$(realpath "$0")")
kubectl apply -f "$script_dir/../argocd/namespace.yaml"

# Install ArgoCD
kubectl apply -n argocd -f https://raw.githubusercontent.com/argoproj/argo-cd/stable/manifests/install.yaml

# Install ArgoCD CLI if not already installed
if ! command -v argocd &> /dev/null
then
    wget https://github.com/argoproj/argo-cd/releases/download/v2.14.9/argocd-linux-amd64
    chmod +x argocd-linux-amd64
    sudo mv argocd-linux-amd64 /usr/local/bin/argocd
fi

# Create repository secret
kubectl apply -f "$script_dir/../argocd/repository.yaml"
