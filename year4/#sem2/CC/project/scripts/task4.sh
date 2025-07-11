#!/bin/bash

cd /home/student/project/cloud-courses

# change "kaethar/cloud-courses-project" to relevant repository name
docker build -t kaethar/cloud-courses-project .
docker login
docker push kaethar/cloud-courses-project:latest

git remote remove origin
git remote add http://gitea-http.gitea.svc.cluster.local:3000/adrian.dumitrache02/nginx-deployment.git
git add .
git commit -m "Add cloud computing project"

kubectl apply -f argocd/website-application.yaml

