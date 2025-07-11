#!/bin/bash

kind create cluster
kubectl cluster-info --context kind-kind
kubectl get nodes

