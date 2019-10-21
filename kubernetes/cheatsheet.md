```
выбрать нужный контекст
pip install awscli
aws configure
aws eks update-kubeconfig --name ...
kubectl config use-context ...

kubectl get pods
kubectl get pods --all-namespaces

kubectl exec -it [container] redis-cli
kubectl port-forward [container] 6379:6379


heml init
для запуска отдельного чарта helm -f 
helm template [путь]
```

Run local k8s
```
/etc/kubernetes/admin.conf -> ~/.kube/config
kubectl get pod

bazel run //docker/datalore:compose-images

cd infra/kubernetes

./scripts/local/start.sh (stop.sh)

kubectl port-forward service/datalore-front 8080

-L8080:127.0.01:8080

1. build.sh
2. deploy.sh
3. change in libs/third_party
```
