# Changelog

This document details everything we have implemented so far for the SongRate project during the second milestone.

Most additions are infrastructure related, we have setup a perfect environment
for starting the development of our application.

## Added

- Set up a Kubernetes Cluster using minikube
- Set up Kong as an API Gateway for our application
  - Now exposed services can be accessed via the gateway IP
- Deployed a PostgreSQL database on the cluster
  - Deployed an Adminer service and connected it to the PostgreSQL database
  - Adminer can now be accessed via the gateway IP at `/adminer`
- Deployed Portainer on the cluster
  - Portainer can now be accessed via the gateway IP at `/portainer` to manage the cluster
- Deployed the `kube-prometheus-stack` (includes Prometheus and Grafana) on the cluster
  - Prometheus can now be accessed via the gateway IP at `/prometheus`
  - Grafana can now be accessed via the gateway IP at `/grafana` and can be used to visualize the metrics collected by Prometheus
- Deployed a GitLab runner on the cluster
  - The runner can now be used to run CI/CD jobs for our application
- Created authentication service using [Supabase](https://supabase.com/) and Go
  - Created DockerHub [image](https://hub.docker.com/r/songrate/auth) for the service
  - Created Kubernetes Deployment and ClusterIP resources for the service
