#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct my_drone
{
    int pos_x;
    int pos_y;
    int drone_id;
    int drone_x;
    int drone_y;
    int emergency;
    int battery;
} mydrone;

typedef struct foe_drone
{
    int drone_id;
    int drone_x;
    int drone_y;
    int emergency;
    int battery;
} foedrone;

typedef struct cnt_creatures
{
    int creature_id;
    int creature_x;
    int creature_y;
    int creature_vx;
    int creature_vy;
    int visible_creature_count;
} creatures;

typedef struct controls
{
    int discharge;
    int escape_mode;
    int my_scan_count;
    int drone_scan_count;
    int drone_id;
    int scan_save;
    int areas;
} controls;

typedef struct radar
{
    int drone_id;
    int creature_id;
    char radar[3];
} radar;

double distance(struct my_drone drone, struct cnt_creatures creature) {
    double dist = sqrt(pow(creature.creature_x - drone.drone_x, 2) + pow(creature.creature_y - drone.drone_y, 2));
    return dist;
}

int main()
{
    struct my_drone mdrone1;
    struct my_drone mdrone2;
    struct foe_drone foedrone;
    struct controls ctrl;
    struct radar radar;
    
    ctrl.areas = 0;
    ctrl.discharge = 0;
    ctrl.scan_save = 0;
    ctrl.escape_mode = 0;
    int light = 1;

    int creature_count;
    scanf("%d", &creature_count);
    for (int i = 0; i < creature_count; i++) {
        int creature_id;
        int color;
        int type;
        scanf("%d%d%d", &creature_id, &color, &type);
    }

    // game loop
    while (1) {
        light = 1;

        int my_score;
        scanf("%d", &my_score);
        int foe_score;
        scanf("%d", &foe_score);

        // MY SAVED SCAN COUNT
        scanf("%d", &ctrl.my_scan_count);
        for (int i = 0; i < ctrl.my_scan_count; i++) {
            int creature_id;
            scanf("%d", &creature_id);
        }

        // ENEMYS SAVED SCAN COUNT
        int foe_scan_count;
        scanf("%d", &foe_scan_count);
        for (int i = 0; i < foe_scan_count; i++) {
            int creature_id;
            scanf("%d", &creature_id);
        }

        // MY DRONE
        int my_drone_count;
        scanf("%d", &my_drone_count);
            scanf("%d%d%d%d%d", &mdrone1.drone_id, &mdrone1.drone_x, &mdrone1.drone_y, &mdrone1.emergency, &mdrone1.battery);
            scanf("%d%d%d%d%d", &mdrone2.drone_id, &mdrone2.drone_x, &mdrone2.drone_y, &mdrone2.emergency, &mdrone2.battery);

        // ENEMY DRONE
        int foe_drone_count;
        scanf("%d", &foe_drone_count);
        for (int i = 0; i < foe_drone_count; i++) {
            scanf("%d%d%d%d%d", &foedrone.drone_id, &foedrone.drone_x, &foedrone.drone_y, &foedrone.emergency, &foedrone.battery);
        }

        // SCAN COUNT
        scanf("%d", &ctrl.drone_scan_count);
        for (int i = 0; i < ctrl.drone_scan_count; i++) {
            int creature_id;
            scanf("%d%d", &ctrl.drone_id, &creature_id);
        }

        // VISIBLE CREATURE COUNT (RADARA GİRİNCE GÖRÜNEN CANLILAR)
        struct cnt_creatures creature;
        
        scanf("%d", &creature.visible_creature_count);
        for (int i = 0; i < creature.visible_creature_count; i++) {
            scanf("%d%d%d%d%d", &creature.creature_id, &creature.creature_x, &creature.creature_y, &creature.creature_vx, &creature.creature_vy);
        }

        // SHOW US WHERE CREATURES POSITIONS
        int radar_blip_count;
        scanf("%d", &radar_blip_count);
        for (int i = 0; i < radar_blip_count; i++) {
            scanf("%d%d%s", &radar.drone_id, &radar.creature_id, radar.radar);
        }

        // Write an action using printf(). DON'T FORGET THE TRAILING \n
        // To debug: fprintf(stderr, "Debug messages...\n;
        // MOVE <x> <y> <light (1|0)> | WAIT <light (1|0)>

        if (ctrl.discharge == 1) // BOŞALTMA ZAMANI
        {
            double dist = distance(mdrone1, creature);
            double dist2 = distance(mdrone2, creature);
            if (dist2 < 1000 && creature.visible_creature_count > 0 && creature.creature_id >= 16 && mdrone2.drone_x > creature.creature_x && mdrone2.drone_y < creature.creature_y)
            {
                fprintf(stderr, "Uzaklik: %lf\n", dist2);
                fprintf(stderr, "Drone 2: Sol alt\n");
                mdrone2.pos_x = mdrone2.drone_x + 600;
                mdrone2.pos_y = mdrone2.drone_y - 600;
            }
            else if (dist2 < 1000 && creature.visible_creature_count > 0 && creature.creature_id >= 16 && mdrone2.drone_x > creature.creature_x && mdrone2.drone_y > creature.creature_y)
            {
                fprintf(stderr, "Uzaklik: %lf\n", dist2);
                fprintf(stderr, "Drone 2: Sol üst\n");
                mdrone2.pos_x = mdrone2.drone_x + 600;
                mdrone2.pos_y = mdrone2.drone_y + 600;
            }
            else if (dist2 < 1000 && creature.visible_creature_count > 0 && creature.creature_id >= 16 && mdrone2.drone_x < creature.creature_x && mdrone2.drone_y > creature.creature_y)
            {
                fprintf(stderr, "Uzaklik: %lf\n", dist2);
                fprintf(stderr, "Uzaklik: %d\n", mdrone2.drone_y);
                fprintf(stderr, "Drone 2: Sağ üst\n");
                mdrone2.pos_x = mdrone2.drone_x - 600;
                mdrone2.pos_y = mdrone2.drone_y + 600;
            }
            else if (dist2 < 1000 && creature.visible_creature_count > 0 && creature.creature_id >= 16 && mdrone2.drone_x < creature.creature_x && mdrone2.drone_y < creature.creature_y)
            {
                fprintf(stderr, "Uzaklik: %lf\n", dist2);
                fprintf(stderr, "Drone 2: Sağ alt\n");
                mdrone2.pos_x = mdrone2.drone_x - 600;
                mdrone2.pos_y = mdrone2.drone_y - 600;
            }
            else
            {
                fprintf(stderr, "Drone 2: Stabil\n");
                mdrone2.pos_x = 500;
                mdrone2.pos_y = 500;
            }

            if (dist < 1500 && creature.visible_creature_count > 0 && creature.creature_id >= 16 && mdrone1.drone_x > creature.creature_x && mdrone1.drone_y < creature.creature_y)
            {
                fprintf(stderr, "Drone 1: Sol alt\n");
                mdrone1.pos_x = mdrone1.drone_x + 600;
                mdrone1.pos_y = mdrone1.drone_y - 600;
            }
            else if (dist < 1500 && creature.visible_creature_count > 0 && creature.creature_id >= 16 && mdrone1.drone_x > creature.creature_x && mdrone1.drone_y > creature.creature_y)
            {
                fprintf(stderr, "Drone 1: Sol üst\n");
                mdrone1.pos_x = mdrone1.drone_x + 600;
                mdrone1.pos_y = mdrone1.drone_y + 600;
            }
            else if (dist < 1500 && creature.visible_creature_count > 0 && creature.creature_id >= 16 && mdrone1.drone_x < creature.creature_x && mdrone1.drone_y > creature.creature_y)
            {
                fprintf(stderr, "Drone 1: Sağ üst\n");
                mdrone1.pos_x = mdrone1.drone_x - 600;
                mdrone1.pos_y = mdrone1.drone_y + 600;
            }
            else if (dist < 1500 && creature.visible_creature_count > 0 && creature.creature_id >= 16 && mdrone1.drone_x < creature.creature_x && mdrone1.drone_y < creature.creature_y)
            {
                fprintf(stderr, "Drone 1: Sağ alt\n");
                mdrone1.pos_x = mdrone1.drone_x - 600;
                mdrone1.pos_y = mdrone1.drone_y - 600;
            }
            else
            {
                fprintf(stderr, "Drone 1: Stabil\n");
                mdrone1.pos_x = 500;
                mdrone1.pos_y = 500;
            }

            printf("MOVE %d %d 0 GOING DISCHARGING\n", mdrone1.drone_x, mdrone1.pos_y);
            printf("MOVE %d %d 0 GOING DISCHARGING\n", mdrone2.drone_x, mdrone2.pos_y);

            if (mdrone1.drone_y < 510 && mdrone2.drone_y < 510)
            {
                ctrl.discharge = 0;
                ctrl.areas = 0;
            }
        }
        else if (ctrl.escape_mode == 1) // BOŞALTMA ZAMANI
        {
            mdrone1.pos_x = 0;
            mdrone1.pos_y = 500;
            printf("MOVE %d %d 0 ESCAPE MODE ON\n",mdrone1.pos_x, mdrone1.pos_y);

            mdrone2.pos_x = 10000;
            mdrone2.pos_y = 500;
            printf("MOVE %d %d 0 ESCAPE MODE ON\n", mdrone2.pos_x, mdrone2.pos_y);
            if (mdrone1.drone_y < 510 || mdrone2.drone_y < 510)
            {
                ctrl.escape_mode = 0;
                ctrl.areas = 0;
            }
        }
        else if (ctrl.areas == 0)
        {
            mdrone1.pos_x = 2000;
            mdrone1.pos_y = 8600;
            mdrone2.pos_x = 6000;
            mdrone2.pos_y = 8600;
            double dist = distance(mdrone1, creature);
            double dist2 = distance(mdrone2, creature);
            if (dist2 < 2000 && creature.visible_creature_count > 0 && creature.creature_id >= 16 && mdrone2.drone_x > creature.creature_x && mdrone2.drone_y < creature.creature_y)
            {
                fprintf(stderr, "2. Uzaklik: %lf\n", dist2);
                fprintf(stderr, "Drone 2: Sol alt\n");
                light = 0;
                mdrone2.pos_x = mdrone2.drone_x + 600;
                mdrone2.pos_y = mdrone2.drone_y - 600;
            }
            else if (dist2 < 2000 && creature.visible_creature_count > 0 && creature.creature_id >= 16 && mdrone2.drone_x > creature.creature_x && mdrone2.drone_y > creature.creature_y)
            {
                fprintf(stderr, "2. Uzaklik: %lf\n", dist2);
                fprintf(stderr, "Drone 2: Sol üst\n");
                light = 0;
                mdrone2.pos_x = mdrone2.drone_x + 600;
                mdrone2.pos_y = mdrone2.drone_y + 600;
            }
            else if (dist2 < 2000 && creature.visible_creature_count > 0 && creature.creature_id >= 16 && mdrone2.drone_x < creature.creature_x && mdrone2.drone_y > creature.creature_y)
            {
                fprintf(stderr, "2. Uzaklik: %lf\n", dist2);
                fprintf(stderr, "Drone 2: Sağ üst\n");
                light = 0;
                mdrone2.pos_x = mdrone2.drone_x - 600;
                mdrone2.pos_y = mdrone2.drone_y + 600;
            }
            else if (dist2 < 2000 && creature.visible_creature_count > 0 && creature.creature_id >= 16 && mdrone1.drone_x < creature.creature_x && mdrone1.drone_y < creature.creature_y)
            {
                fprintf(stderr, "2. Uzaklik: %lf\n", dist2);
                fprintf(stderr, "Drone 2: Sağ alt\n");
                light = 0;
                mdrone2.pos_x = mdrone2.drone_x - 600;
                mdrone2.pos_y = mdrone2.drone_y - 600;
            }
            
            if (dist < 2000 && creature.visible_creature_count > 0 && creature.creature_id >= 16 && mdrone1.drone_x > creature.creature_x && mdrone1.drone_y < creature.creature_y)
            {
                fprintf(stderr, "Uzaklik: %lf\n", dist);
                fprintf(stderr, "Drone 1: Sol alt\n");
                light = 0;
                mdrone1.pos_x = mdrone1.drone_x + 600;
                mdrone1.pos_y = mdrone1.drone_y - 600;
                ctrl.discharge = 1;
            }
            else if (dist < 2000 && creature.visible_creature_count > 0 && creature.creature_id >= 16 && mdrone1.drone_x > creature.creature_x && mdrone1.drone_y > creature.creature_y)
            {
                fprintf(stderr, "Uzaklik: %lf\n", dist);
                fprintf(stderr, "Drone 1: Sol üst\n");
                light = 0;
                mdrone1.pos_x = mdrone1.drone_x + 600;
                mdrone1.pos_y = mdrone1.drone_y + 600;
            }
            else if (dist < 2000 && creature.visible_creature_count > 0 && creature.creature_id >= 16 && mdrone1.drone_x < creature.creature_x && mdrone1.drone_y > creature.creature_y)
            {
                fprintf(stderr, "Uzaklik: %lf\n", dist);
                fprintf(stderr, "Drone 1: Sağ üst\n");
                light = 0;
                mdrone1.pos_x = mdrone1.drone_x - 600;
                mdrone1.pos_y = mdrone1.drone_y + 600;
            }
            else if (dist < 2000 && creature.visible_creature_count > 0 && creature.creature_id >= 16 && mdrone1.drone_x < creature.creature_x && mdrone1.drone_y < creature.creature_y)
            {
                fprintf(stderr, "Uzaklik: %lf\n", dist);
                fprintf(stderr, "Drone 1: Sağ alt\n");
                light = 0;
                mdrone1.pos_x = mdrone1.drone_x - 600;
                mdrone1.pos_y = mdrone1.drone_y - 600;
                ctrl.discharge = 1;
            }

            // if (mdrone1.drone_y == 8600 || mdrone2.drone_y == 8600)
            //     ctrl.discharge = 1;

            if (mdrone1.drone_y > 2500)
                printf("MOVE %d %d %d GOING FIRST AREA\n",mdrone1.pos_x,mdrone1.pos_y, light);
            else
                printf("MOVE %d %d %d GOING FIRST AREA\n",mdrone1.pos_x,mdrone1.pos_y, 0);

            if (mdrone2.drone_y > 2500)
                printf("MOVE %d %d %d GOING FIRST AREA\n",mdrone2.pos_x,mdrone2.pos_y, light);
            else
                printf("MOVE %d %d %d GOING FIRST AREA\n",mdrone2.pos_x,mdrone2.pos_y, 0);
        }
        else if (ctrl.areas == 1)
        {
            ctrl.discharge = 1;
        }

        // if (radar.radar[0] == 'B' && radar.radar[1] == 'L' && radar.creature_id < 16)
        // {
        //     mdrone1.drone_x -= 500;
        //     mdrone1.drone_y += 500;

        // }
        // else if (radar.radar[0] == 'B' && radar.radar[1] == 'R' && radar.creature_id < 16)
        // {

        //     mdrone1.drone_x += 500;
        //     mdrone1.drone_y += 500;
        // }
        // else if (radar.radar[0] == 'T' && radar.radar[1] == 'L' && radar.creature_id < 16)
        // {
        //     mdrone1.drone_x -= 500;
        //     mdrone1.drone_y -= 500;

        // }
        // else if (radar.radar[0] == 'T' && radar.radar[1] == 'R' && radar.creature_id < 16)
        // {
        //     mdrone1.drone_x += 500;
        //     mdrone1.drone_y -= 500;
        // }
        
        // if (radar.radar[0] == 'B' && radar.radar[1] == 'L' && radar.creature_id >= 16)
        // {
        //     mdrone1.drone_x += 500;
        //     mdrone1.drone_y -= 500;

        // }
        // else if (radar.radar[0] == 'B' && radar.radar[1] == 'R' && radar.creature_id >= 16)
        // {

        //     mdrone1.drone_x -= 500;
        //     mdrone1.drone_y -= 500;
        // }
        // else if (radar.radar[0] == 'T' && radar.radar[1] == 'L' && radar.creature_id >= 16)
        // {
        //     mdrone1.drone_x += 500;
        //     mdrone1.drone_y += 500;

        // }
        // else if (radar.radar[0] == 'T' && radar.radar[1] == 'R' && radar.creature_id >= 16)
        // {
        //     mdrone1.drone_x -= 500;
        //     mdrone1.drone_y += 500;
        // }
        

        // printf("MOVE %d %d 0\n", mdrone1.drone_x, mdrone1.drone_y);
        // printf("MOVE 5000 5000 0 monster in the top right\n");

        
    }

    return 0;
}