#!/bin/bash

# Create namespace for Gitea
script_dir=$(dirname "$(realpath "$0")")
kubectl apply -f "$script_dir/../gitea"

# Add Gitea Helm repository
helm repo add gitea-charts https://dl.gitea.com/charts/
helm repo update

# Install Gitea to the gitea namespace
helm install -n gitea gitea gitea-charts/gitea
