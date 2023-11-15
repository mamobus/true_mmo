#define dSINGLE
#include <ode/ode.h>
#include <windows.h>
#include <assert.h>

int main()
{   
    printf("start\n");
    dInitODE();
    
    dWorldID world = dWorldCreate();
    dWorldSetGravity(world, 0.1, 0.1, -10.0);
    dWorldSetDamping(world, 1e-4, 1e-5);
    dSpaceID space = dHashSpaceCreate(0);

    dMass mass = {};
    dBodyID  body  = dBodyCreate(world);
    dBodySetPosition(body, 1.0, 1.0, 1.0);
    dBodySetLinearVel(body, 1.0, 1.0, 1.0);
    dBodySetAngularVel(body, 0, 0, 0);
    dBodySetGravityMode(body, 1);
    dBodyEnable(body);

    // dMassSetZero(&mass);
    mass.mass = 1.0;
    dMassSetSphere(&mass, 1.0, 1.0);
    dBodySetMass(body, &mass);

    dGeomID geom = dCreateSphere(space, 1.0);
    dGeomSetBody(geom, body);

    dVector3* pos = dBodyGetPosition(body);
    printf("pos %.1f %.1f %.1f %.1f\n", pos[0], pos[1], pos[2], pos[3]);
    dVector3* vel = dBodyGetPosition(body);
    printf("vel %.1f %.1f %.1f %.1f\n", vel[0], vel[1], vel[2], vel[3]);

    for (int i=0; i < 100; i++)
    {
        dVector3 grav;
        assert(dBodyIsEnabled(body)==1); 
        dWorldGetGravity(world, &grav);
        printf("grav %.1f %.1f %.1f %.1f\n", grav[0], grav[1], grav[2], grav[3]);

        assert(dBodyGetGravityMode(body)==1);


        dVector3* frc =  dBodyGetForce(body);
        printf("force_before %.1f %.1f %.1f %.1f\n", frc[0], frc[1], frc[2], frc[3]);

        Sleep(50); //50 ms
        assert(dWorldStep(world, 0.05) == 1);

        frc =  dBodyGetForce(body);
        printf("force_after %.1f %.1f %.1f %.1f\n", frc[0], frc[1], frc[2], frc[3]);


        frc =  dBodyGetForce(body);
        printf("grav %.1f %.1f %.1f %.1f\n", frc[0], frc[1], frc[2], frc[3]);
        pos = dBodyGetPosition(body);
        printf("pos %.1f %.1f %.1f %.1f\n", pos[0], pos[1], pos[2], pos[3]);
        printf("pos %.1f %.1f %.1f %.1f\n\n", pos[0], pos[1], pos[2], pos[3]);
    }

    dWorldDestroy(world);
}