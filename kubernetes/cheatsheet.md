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


kubectl top nodes
kubectl top pods -n kapot-prod

События OOM-kill: kubectl get events --field-selector reason=OOMKilling





### Подключение к внешнему k8s
export KUBECONFIG=/home/laptop/Downloads/twc-kapot.ru-prodk8s-config.yaml

либо

kubectl --kubeconfig=kubeconfig.yaml <команда>




kubectl create namespace kapot-prod



kubectl -n kapot-stage create secret generic backend-secrets \
  --from-literal=DATABASE_URL="postgresql://...@192.168.0.4:5432/default_db" \
  --from-literal=JWT_SECRET="..." \
  --from-literal=AWS_ACCESS_KEY_ID=... \
  --from-literal=AWS_SECRET_ACCESS_KEY=...
  
kubectl describe secret backend-secrets -n kapot-prod
kubectl get secret backend-secrets -o yaml -n kapot-prod
  
  
kubectl -n kapot-stage create secret docker-registry regcred \
  --docker-server="registry.gitlab.com/garnet-lab/kapot/kapot" \
  --docker-username="..." \
  --docker-password="..."
  
  

TLS
cert-manager
https://timeweb.cloud/docs/k8s/addons/cert-manager


Авторизация Basic Auth в Ingress NGINX
htpasswd -c auth kapot
kubectl create secret generic basic-auth --from-file=auth -n kapot-stage
kubectl get secret basic-auth -o yaml -n kapot-stage






# Preview (optional)
kubectl kustomize deploy/k8s/overlays/prod

kubectl kustomize build deploy/k8s/overlays/prod/
kubectl kustomize deploy/k8s/base/
kubectl kustomize deploy/k8s/overlays/prod
kubectl kustomize deploy/k8s/overlays/prod build
kubectl kustomize deploy/k8s/overlays/prod/kustomization.yaml 


# Apply (creates namespace via overlay patch, services, deployments, ingress)
kubectl apply -k deploy/k8s/overlays/prod
kubectl apply -k deploy/k8s/overlays/prod/loadbalancer.yaml


Базовый пример с LoadBalancer
https://timeweb.cloud/docs/k8s/addons/nginx-ingress

`kubectl get nodes` - вывести список всех запущенных нод

`kubectl get pods` - вывести список всех запущенных подов

### Сборка и запуск локального приложения
Скачать Minikube: https://minikube.sigs.k8s.io/docs/start/

Для сборки образа и запуска деплоймента:
```
eval $(minikube docker-env)
docker build -t my-app:latest .
kubectl apply -f deployment.yaml
```

kubectl logs deployment/backend --all-pods=true -n kapot-prod

kubectl exec -it backend-558fdd9669-2tw8p -n kapot-prod -- sh

kubectl -n kapot-prod port-forward service/frontend 8000
kubectl -n ingress-nginx port-forward ingress-nginx-controller-68wvs 8080:80
Port-forward in stage: kubectl -n <ns> port-forward svc/prisma-studio 5555:5555 and open http://localhost:5555.

kubectl get ingress --all-namespaces
kubectl get all --all-namespaces



helm template kapot . -f ./values-prod.yaml -n kapot-prod --set backend.image.tag="fucker!" | less
--dry-run
helm uninstall kapot -n kapot-prod

helm upgrade --install kapot deploy/helm -n "kapot-prod" --create-namespace -f deploy/helm/values-prod.yaml --wait --wait-for-jobs --timeout 10m --reuse-values --debug
helm template kapot . -n kapot-stage -f ./values-stage.yaml --show-only templates/init-job.yaml --set backend.image.tag="0f885260" --set initJob.flags.INIT_CLEAR=true --set initJob.flags.INIT_SEED=true | kubectl -n kapot-stage apply -f -
kubeckubectl get pods -n cert-manager
kubectl create namespace kapot-prod
kubectl create secret generic basic-auth --from-file=auth -n kapot-prod
kubectl delete pod -l app.kubernetes.io/component=controller -ningress-nginx
kubectl delete service ingress-nginx-controller -n ingress-nginx
kubectl delete service ingress-nginx-controller -n kapot-prod
kubectl describe pod frontend-65ff6bf87b-r9kbt -n kapot-prod
kubectl describe secret backend-secrets -n kapot-prod
kubectl describe service/ingress-nginx-controller -n ingress-nginx
kubectl dlogs frontend-65ff6bf87b-r9kbt -n kapot-prod
kubectl exec -it backend-558fdd9669-2tw8p -n kapot-prod -- sh
kubectl get all --all-namespaces
kubectl get ingress --all-namespaces
kubectl get jobs --all-namespaces
kubectl get nodes
kubectl get nodes -A
kubectl get pods --all-namespaces
kubectl get pods -n kapot-prod
kubectl get secret backend-secrets -o yaml -n kapot-prod
kubectl get secret regcred -o yaml -n kapot-prod
kubectl get services --all-namespaces
kubectl logs deployment/frontend --all-pods=true -n kapot-prod --tail 100 --timestamps
kubectl logs prisma-migrate-gnvtl -n kapot-prod
kubectl logs prisma-migrate-x8twj -n kapot-prod
kubectl -n ingress-nginx get services
kubectl -n ingress-nginx port-forward ingress-nginx-controller-68wvs
kubectl -n ingress-nginx port-forward ingress-nginx-controller-68wvs 8080:80
kubectl -n ingress-nginx port-forward service/ingress 80
kubectl -n kapot-prod apply -f deploy/k8s/base/prisma-migrate-job.yaml
kubectl -n kapot-prod create secret docker-registry regcred   --docker-server="registry.gitlab.com/garnet-lab/kapot/kapot"   --docker-username="..."   --docker-password="..."
kubectl -n kapot-prod delete job prisma-migrate --ignore-not-found
kubectl -n kapot-prod logs ingress-nginx-controller-68wvs
kubectl -n kapot-prod port-forward service/frontend 8000
kubectl -n kapot-prod port-forward service/frontend 8080
kubectl -n kapot-prod port-forward service/ingress 80
kubectl port-forward service/frontend 8080
kubectl rollout restart service/ingress-nginx-controller -n ingress-nginx

kubectl get pod/kubernetes-dashboard-web-84b6c6fdf8-bfgzv -n kubernetes-dashboard -o yaml | kubectl replace --force -f -


https://github.com/kubernetes/ingress-nginx/blob/main/docs/user-guide/nginx-configuration/annotations.md
https://github.com/kubernetes/ingress-nginx/blob/main/docs/user-guide/nginx-configuration/configmap.md

Kubernetes Dashboard

Timeweb Manages K8S

app:
  ingress:
    enabled: true
    hosts:
      - dashboard.kpt-prod.garnet-lab.com
    useDefaultIngressClass: true
    issuer:
      name: letsencrypt-cert
      scope: cluster
cert-manager:
  enabled: false


локально установить зависимости
helm dependency update ./deploy/helm/
